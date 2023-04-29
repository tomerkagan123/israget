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
struct UploadItemRequest {
	std::string userName;
	std::string itemName;
	std::string description;
	std::string price;
	std::string email;
};
class JsonRequestPacketDeserializer {
public:
	//v1.0.2
	LoginRequest deserializeLoginRequest(std::string buffer);
	SignUpRequest deserializeSignUpRequest(std::string buffer);
	UploadItemRequest deserializeUploadItemRequest(std::string buffer);
	//v2.0.0
	/*GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(std::string buffer);
	CreateRoomRequest deserializeCreateRoomRequest(std::string buffer);
	JoinRoomRequest deserializeJoinRoomRequest(std::string buffer);*/
};