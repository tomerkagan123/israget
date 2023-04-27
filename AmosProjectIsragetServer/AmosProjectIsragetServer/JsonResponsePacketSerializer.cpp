#include "JsonResponsePacketSerializer.h"
#include <iostream>
#include "json.hpp"
#include <vector>
#include <string>
//MESSAGE CODES:
//'L' - LOGIN
//'S' - SIGN UP
//'E' - ERROR
//'O' - LOGOUT
//'R' - GET ROOMS
//'P' - GET PLAYERS IN ROOM
//'J' - JOIN ROOM
//'C' - CREATE ROOM
//'H' - HIGH SCORE
//'T' - STATISTICS
using json = nlohmann::json;

//This function returns the 4 bytes of the size section in the protocol
std::vector<int> getSizeVector(int size)
{
	std::vector<int> sizeInBytes{ 0, 0, 0, 0 };
	for (int i = 3; i >= 0; i--) {
		if (size <= 127) { //127 is the last number of the ascii table
			for (int j = i; j > 0; j--) {
				sizeInBytes[j] = 0;
			}
			sizeInBytes[i] = size;
			break;
		}
		else if (size > 127) {
			sizeInBytes[i] = 127;
			size = size - 127;
		}
	}
	return sizeInBytes;
}

std::string JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse msg)
{
	std::string msgFormat = "L"; // L = login code
	json j = {
		{"status", msg.status}
	};
	int size = j.dump().size();
	std::vector<int> sizeInBytes = getSizeVector(size);
	
	for (int i = 0; i < 4; i++)
	{
		char asciiVal = (char)sizeInBytes[i];
		msgFormat.append(1, asciiVal);
	}
	
	msgFormat = msgFormat + j.dump();
	return msgFormat;
}

std::string JsonResponsePacketSerializer::serializeSignUpResponse(SignUpResponse msg)
{
	std::string msgFormat = "S"; // S = sign up code
	json j = {
		{"status", msg.status}
	};
	int size = j.dump().size();
	std::vector<int> sizeInBytes = getSizeVector(size);

	for (int i = 0; i < 4; i++)
	{
		char asciiVal = (char)sizeInBytes[i];
		msgFormat.append(1, asciiVal);
	}

	msgFormat = msgFormat + j.dump();
	return msgFormat;
}

std::string JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse msg)
{
	std::string msgFormat = "E"; // E = error code
	int size = msg.message.size();
	std::vector<int> sizeInBytes = getSizeVector(size);

	for (int i = 0; i < 4; i++)
	{
		char asciiVal = (char)sizeInBytes[i];
		msgFormat.append(1, asciiVal);
	}

	json j = {
		{"message", msg.message}
	};
	msgFormat = msgFormat + j.dump();
	return msgFormat;
}

std::string JsonResponsePacketSerializer::serializeLogoutResponse(LogoutResponse msg)
{
	std::string msgFormat = "O"; // O = logout code
	json j = {
		{"status", msg.status}
	};

	int size = j.dump().size();
	std::vector<int> sizeInBytes = getSizeVector(size);

	for (int i = 0; i < 4; i++)
	{
		char asciiVal = (char)sizeInBytes[i];
		msgFormat.append(1, asciiVal);
	}

	msgFormat = msgFormat + j.dump();
	return msgFormat;
}
