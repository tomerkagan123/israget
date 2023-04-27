#pragma once
#include <iostream>
#include <vector>

struct LoginRequest {
	std::string username;
	std::string password;
};
struct SignUpRequest {
	std::string username;
	std::string password;
	std::string email;
};
struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};
struct JoinRoomRequest {
	unsigned int roomId;
};
struct GetPlayersInRoomRequest {
	unsigned int roomId;
};
class JsonRequestPacketDeserializer {
public:
	//v1.0.2
	LoginRequest deserializeLoginRequest(std::string buffer);
	SignUpRequest deserializeSignUpRequest(std::string buffer);
	//v2.0.0
	GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(std::string buffer);
	CreateRoomRequest deserializeCreateRoomRequest(std::string buffer);
	JoinRoomRequest deserializeJoinRoomRequest(std::string buffer);
};