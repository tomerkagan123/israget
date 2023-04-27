#include "MenuRequestHandler.h"
#include "SqliteDatabase.h"
#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
//MESSAGE CODES:
//'L' - LOGIN
//'S' - SIGN UP
//'E' - ERROR
//'O' - LOGOUT
//'R' - GET ITEMS WITH..
//'P' - GET STATS ABOUT ITEM - ITEM_NAME, USER_ID, DATE, DESCRIPTION, IMAGE
//'U' - UPLOAD ITEM
//'X' - DELETE ITEM

using json = nlohmann::json;
MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory* reqHandlerFactory)
{
	this->m_user = user;
	this->m_handlerFactory = reqHandlerFactory;
}
bool MenuRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	if (requestInfo.requestId == (int)'O' || requestInfo.requestId == (int)'R' || 
		requestInfo.requestId == (int)'P' || requestInfo.requestId == (int)'C'
		|| requestInfo.requestId == (int)'J' || requestInfo.requestId == (int)'T' || requestInfo.requestId == (int)'H')
	{
		return true;
	}
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	SqliteDatabase db;
	JsonRequestPacketDeserializer jsonDeserialize;
	std::string stringBuffer(requestInfo.buffer.begin(), requestInfo.buffer.end()); //converts char buffer to std::string

	if (requestInfo.requestId == (int)'O' || requestInfo.requestId == (int)'D')
	{
		result = this->signout(requestInfo);
	}
	return result;
}

RequestResult MenuRequestHandler::signout(RequestInfo requestInfo)
{
	RequestResult result;
	SqliteDatabase db;
	JsonRequestPacketDeserializer jsonDeserialize;
	std::string username = this->m_user.getName();
	if (db.doesUserExist(username))
	{
		result.response = "Logout successful";
		result.newHandler = this->m_handlerFactory->createLoginRequestHandler(); //sends user back to login
	}
	else
	{
		result.response = "Logout unsuccessful";
		result.newHandler = this; //stays at the current page
	}
	return result;
}
