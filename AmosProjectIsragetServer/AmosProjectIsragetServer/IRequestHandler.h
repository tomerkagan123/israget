#pragma once
#include <iostream>
#include <vector>
#include <ctime>


struct RequestResult; //declares the class
struct RequestInfo {
	int requestId;
	time_t timeOfRecieve;
	std::vector<char> buffer;
};

class IRequestHandler {
public:
	virtual bool isRequestRelevant(RequestInfo requestInfo) const = 0;
	virtual RequestResult handleRequest(RequestInfo requestInfo) = 0;
};

struct RequestResult {
	std::string response;
	IRequestHandler* newHandler;
};