#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <fstream>
#include <mutex>
#include <vector>
#include "Helper.h"
#include "Communicator.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "MenuRequestHandler.h"
// using static const instead of macros 
static const unsigned short PORT = 5555;
static const unsigned int IFACE = 0;


using std::string;
using std::mutex;
using std::unique_lock;
using std::vector;
void serverConsoleInput();
void Server::run()
{
	m_communicator.bindAndListen();
	std::thread inputThread(serverConsoleInput); //lets the server side type commands (EXIT to shut down program)
	inputThread.detach();
	
	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		TRACE("accepting client...");
		m_communicator.startHandleRequests();
	}
}


void serverConsoleInput()//gives server side access to typing in console with threads
{
	while (true)
	{
		std::string input = "";
		std::cin >> input;
		if (input == "EXIT")
		{
			exit(0);
		}
	}
}
