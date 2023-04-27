#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory()
{
    this->m_database = new SqliteDatabase();
    this->m_loginManager = *(new LoginManager());
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    LoginRequestHandler* logReqHandler = new LoginRequestHandler(&(this->m_loginManager),this);
    return logReqHandler;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser loggedUser)
{   
    MenuRequestHandler* menuReqHandler = new MenuRequestHandler(loggedUser, this);
    return menuReqHandler;
}
