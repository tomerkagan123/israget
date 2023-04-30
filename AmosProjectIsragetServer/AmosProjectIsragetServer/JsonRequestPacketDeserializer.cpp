#define _CRT_SECURE_NO_WARNINGS
#include "JsonRequestPacketDeserializer.h"
#include <iostream>
#include <string>
#include <regex>
#include <string.h>
#include "json.hpp"

using json = nlohmann::json;
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::string buffer)
{
    LoginRequest request;
    buffer.erase(0, 5); //removes the 5 bytes of the message, code + message length
    json jsonParse = json::parse(buffer);

    request.username = jsonParse.value("username", "NULL");
    request.password = jsonParse.value("password", "NULL");

    return request;
}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::string buffer)
{
    SignUpRequest request;
    buffer.erase(0, 5); //removes the 5 bytes of the message, code + message length
    json jsonParse = json::parse(buffer);

    request.username = jsonParse.value("username", "NULL");
    request.password = jsonParse.value("password", "NULL");
    request.email = jsonParse.value("email", "NULL");

    return request;
}

UploadItemRequest JsonRequestPacketDeserializer::deserializeUploadItemRequest(std::string buffer)
{
    buffer.erase(0, 5);
    std::cout << buffer << std::endl;
    json jsonParse = json::parse(buffer);
    UploadItemRequest request;
    request.userName = jsonParse.value("userName", "NULL");
    request.itemName = jsonParse.value("itemName", "NULL");
    request.description = jsonParse.value("description", "NULL");
    request.price = jsonParse.value("price", "NULL");
    request.email = jsonParse.value("email", "NULL");
    return request;
}

GetSpecItemRequest JsonRequestPacketDeserializer::deserializeGetSpecItemRequest(std::string buffer)
{
    buffer.erase(0, 5);
    std::cout << buffer << std::endl;
    json jsonParse = json::parse(buffer);
    GetSpecItemRequest request;
    request.name = jsonParse.value("name", "NULL");
    return request;
}

/*GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(std::string buffer)
{
    GetPlayersInRoomRequest request;
    buffer.erase(0, 5); //removes the 5 bytes of the message, code + message length
    json jsonParse = json::parse(buffer);

    request.roomId = jsonParse.value("roomId", 0);
    
    return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::string buffer)
{
    CreateRoomRequest request;
    buffer.erase(0, 5); //removes the 5 bytes of the message, code + message length
    json jsonParse = json::parse(buffer);
    
    request.roomName = jsonParse.value("roomName", "NULL");
    request.maxUsers = jsonParse.value("maxUsers", 10);
    request.questionCount = jsonParse.value("questionCount", 10);
    request.answerTimeout = jsonParse.value("answerTimeout", 10);

    return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::string buffer)
{
    JoinRoomRequest request;
    buffer.erase(0, 5); //removes the 5 bytes of the message, code + message length
    json jsonParse = json::parse(buffer);

    request.roomId = jsonParse.value("roomId", 0);

    return request;
}*/
