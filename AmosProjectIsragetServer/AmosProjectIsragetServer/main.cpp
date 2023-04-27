#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include "Helper.h"
#include "Communicator.h"
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>
//#include "JsonResponsePacketSerializer.h"
// In a lot of places in the code we pass to function constant reference (const Bla&)
// to an object and not the object itself, 

int main()
{
	// Q: why is this try necessarily ?
	// A: we want to know what happened that made the server crush
	try
	{

		TRACE("Starting...");
		// NOTICE at the end of this block the WSA will be closed 
		WSAInitializer wsa_init;
		Server server;
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception in main !" << std::endl;
	}
}
