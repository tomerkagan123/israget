#pragma once
#include <iostream>
#include <vector>
struct LoginResponse {
	unsigned int status;
};
struct SignUpResponse {
	unsigned int status;
};
struct ErrorResponse {
	std::string message;
};
struct LogoutResponse {
	unsigned int status;
};
class JsonResponsePacketSerializer {
public:
	//v1.0.2
	static std::string serializeLoginResponse(LoginResponse msg);
	static std::string serializeSignUpResponse(SignUpResponse msg);
	static std::string serializeErrorResponse(ErrorResponse msg);
	//v2.0.0
	static std::string serializeLogoutResponse(LogoutResponse msg);
};