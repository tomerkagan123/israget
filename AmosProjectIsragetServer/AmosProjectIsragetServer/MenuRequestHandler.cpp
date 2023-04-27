#include "MenuRequestHandler.h"
#include "SqliteDatabase.h"
#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
//MESSAGE CODES:
//'L' - LOGIN
//'S' - SIGN UP
//'E' - ERROR
//'O' - LOGOUT
//'R' - GET ALL ITEMS
//'F' - GET ITEMS THAT CONTAIN:
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
	else if (requestInfo.requestId == (int)'R')
	{
		result = this->getItems(requestInfo);
	}
	else if (requestInfo.requestId == (int)'P')
	{
		result = this->getItemInfo(requestInfo);
	}
	else if (requestInfo.requestId == (int)'U')
	{
		result = this->uploadItem(requestInfo);
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

RequestResult MenuRequestHandler::getItems(RequestInfo requestInfo)
{
	RequestResult result;
	SqliteDatabase db;
	JsonRequestPacketDeserializer jsonDeserialize;
	std::list<Item> itlist = db.getItems();
	result.response = "Items";
	int i = 0;
	for (auto item : itlist)
	{
		result.response = result.response + ';' + item.user_name + ':' + item.item_name + ':' + item.description + ':' + std::to_string(item.price) + ':' + item.email;
		if (i < itlist.size() - 1)
		{
			result.response = result.response + ',';
		}
		i++;
	}
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::getItemInfo(RequestInfo requestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::uploadItem(RequestInfo requestInfo)
{
	return RequestResult();
}
