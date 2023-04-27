#include "LoginRequestHandler.h"
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "MenuRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "SqliteDatabase.h"

LoginRequestHandler::LoginRequestHandler(LoginManager* logMan,RequestHandlerFactory* reqFact)
{
    this->m_loginManager = logMan;
    this->m_handlerFactory = reqFact;
}
bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
    if (requestInfo.requestId == int('L') || requestInfo.requestId == int('S')) {
        return true;
    }
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo)
{
    RequestResult result;
    JsonRequestPacketDeserializer j;
    if (requestInfo.requestId == (int)'L')
    {
        LoginManager logManager;
        LoginRequest logReq;
        
        std::string stringBuffer(requestInfo.buffer.begin(), requestInfo.buffer.end()); //converts char buffer to std::string
        logReq = j.deserializeLoginRequest(stringBuffer);
        std::cout << logReq.username << "     " << logReq.password << std::endl;
        bool login = logManager.login(logReq.username, logReq.password);

        if (login)
        {
            result.response = "Login Successful";
            result.newHandler = new MenuRequestHandler(LoggedUser(logReq.username), this->m_handlerFactory);
        }
        else 
        {
            result.response = "Login Failed";
            result.newHandler = this->m_handlerFactory->createLoginRequestHandler();
        }
    }
    else if (requestInfo.requestId == (int)'S') 
    {
        SignUpRequest signUpReq;
        LoginManager logManager;
        SqliteDatabase db;


        std::string stringBuffer(requestInfo.buffer.begin(), requestInfo.buffer.end()); //converts char buffer to std::string
        signUpReq = j.deserializeSignUpRequest(stringBuffer);
        std::cout << signUpReq.username << "     " << signUpReq.password << "     " << signUpReq.email << std::endl;
        if (db.doesUserExist(signUpReq.username)) //checks if the username already exists before signing up
        {
            result.response = "Sign Up Failed";
            result.newHandler = this->m_handlerFactory->createLoginRequestHandler(); 
        }
        else
        {
            logManager.signup(signUpReq.username, signUpReq.password, signUpReq.email);
            result.response = "Sign Up Succeeded";
            result.newHandler = this->m_handlerFactory->createLoginRequestHandler();
        }
    }
    else 
    {
        result.response = "Error";
        result.newHandler = nullptr;
    }
    return result;
}

RequestResult LoginRequestHandler::login()
{
    return RequestResult();
}

RequestResult LoginRequestHandler::signup()
{
    return RequestResult();
}

