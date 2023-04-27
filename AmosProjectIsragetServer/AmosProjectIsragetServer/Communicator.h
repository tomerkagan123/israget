#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include "IRequestHandler.h"
#include <map>
#include "RequestHandlerFactory.h"
class Communicator
{
public:
	void startHandleRequests();
	void bindAndListen();
	Communicator();
	~Communicator();

private:
	RequestHandlerFactory* m_handlerFactory;
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	void handleNewClient(SOCKET sock);
};