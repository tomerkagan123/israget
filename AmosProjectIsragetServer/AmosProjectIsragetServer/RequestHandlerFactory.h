#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "SqliteDatabase.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"

//forward declaration
class MenuRequestHandler;
class LoginRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser loggedUser);
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};