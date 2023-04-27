#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

class LoginManager;
class RequestHandlerFactory;
class LoginRequestHandler : public IRequestHandler {
public:
	LoginRequestHandler(LoginManager* logMan, RequestHandlerFactory* reqFact);
	virtual bool isRequestRelevant(RequestInfo requestInfo) const override;
	virtual RequestResult handleRequest(RequestInfo requestInfo) override;
	RequestResult login();
	RequestResult signup();

private:
	LoginManager* m_loginManager;
	RequestHandlerFactory* m_handlerFactory;
};