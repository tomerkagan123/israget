#include "Communicator.h"
#include "Helper.h"
#include <WinSock2.h>
#include <Windows.h>
#include <thread>
#include <ctime>
#include <chrono>
#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include <mutex>
//FIRST LETTER MUST BE A
std::mutex lock;
MenuRequestHandler* globalMenuRequest;

Communicator::Communicator()
{
	this->m_handlerFactory = new RequestHandlerFactory();
	// notice that we step out to the global namespace
	// for the resolution of the function socket
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	TRACE(__FUNCTION__ " closing accepting socket");
	// why is this try necessarily ?
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(m_serverSocket);
	}
	catch (...) {}
}
void Communicator::startHandleRequests()
{
	SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted !");
	//pair to add to map
	std::pair<SOCKET,IRequestHandler*> client;
	client.first = client_socket;
	client.second = this->m_handlerFactory->createLoginRequestHandler();
	this->m_clients.insert(client);
	// create new thread for client	and detach from it
	std::thread tr(&Communicator::handleNewClient, this, client_socket);
	tr.detach();
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(5555);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = 0;
	// again stepping out to the global namespace
	if (::bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}

void Communicator::handleNewClient(SOCKET sock)
{
	try
	{
		LoginRequestHandler *loginHandler = this->m_handlerFactory->createLoginRequestHandler();
		RequestInfo reqInfo;
		RequestResult reqResult;
		// get the first message code
		std::vector<char> buffer;
		bool flagFirstTime = false;
		bool flag = false;
		char msg[1025];
		std::map<SOCKET, IRequestHandler*>::iterator it = this->m_clients.find(sock);
		while (true)
		{
			int i = 0;
			recv(sock, msg, 1025, 0);
			msg[1024] = 0;
			reqInfo.timeOfRecieve = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			reqInfo.requestId = msg[0];
			while (msg[i] != -52 && !flag)
			{
				buffer.push_back(msg[i]);
				i++;
			}
			reqInfo.buffer = buffer;
			for (char i : reqInfo.buffer)
			{

				std::cout << i;
			}
			std::cout << std::endl;
			bool isRelevant;
			lock.lock();

			if (reqInfo.requestId == 'D') // 'D' for disconnect 
			{
				if(flagFirstTime) //if logged in, sign out before disconnecting.
					reqResult.newHandler->handleRequest(reqInfo);
				lock.unlock();
				break;
			}

			if (!flagFirstTime)
				isRelevant = loginHandler->isRequestRelevant(reqInfo);
			else
				isRelevant = reqResult.newHandler->isRequestRelevant(reqInfo);
			if (isRelevant && !flagFirstTime)
			{
				reqResult = loginHandler->handleRequest(reqInfo);
				std::cout << reqResult.response << std::endl;
				send(sock, reqResult.response.c_str(), reqResult.response.size(), 0);
				flagFirstTime = true;
			}
			else if(isRelevant)
			{
				it->second = reqResult.newHandler;
				reqResult = it->second->handleRequest(reqInfo);
				std::cout << reqResult.response << std::endl;
				send(sock, reqResult.response.c_str(), reqResult.response.size(), 0);
			}
			else
			{
				if (flagFirstTime) //if logged in, sign out before disconnecting.
					reqResult.newHandler->handleRequest(reqInfo);
				lock.unlock();
				break;
			}
			lock.unlock();
			reqInfo.buffer.clear();
			buffer.clear();
			reqResult.response.clear();
			memset(msg, 0, sizeof msg);
		}
	}
	catch (const std::exception& e)
	{
		e.what();
	}
	::closesocket(sock);
}