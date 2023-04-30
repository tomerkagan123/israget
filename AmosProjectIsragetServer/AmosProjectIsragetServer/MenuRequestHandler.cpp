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
//'C' - UPLOAD ITEM
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
		requestInfo.requestId == (int)'F' || requestInfo.requestId == (int)'C'
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
	else if (requestInfo.requestId == (int)'F')
	{
		result = this->getSpecItems(requestInfo);
	}
	else if (requestInfo.requestId == (int)'C')
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
		result.response = result.response + ';' + item.user_name + ':' + item.item_name + ':' + item.description + ':' + item.price + ':' + item.email;
		if (i < itlist.size() - 1)
		{
			result.response = result.response + ',';
		}
		i++;
	}
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::getSpecItems(RequestInfo requestInfo)
{
	RequestResult result;
	SqliteDatabase db;
	std::string stringBuffer(requestInfo.buffer.begin(), requestInfo.buffer.end()); //converts char buffer to std::string
	JsonRequestPacketDeserializer jsonDeserialize;
	GetSpecItemRequest request = jsonDeserialize.deserializeGetSpecItemRequest(stringBuffer);
	std::list<Item> itlist = db.getSpecItems(request.name);
	result.response = "Items";
	int i = 0;
	for (auto item : itlist)
	{
		result.response = result.response + ';' + item.user_name + ':' + item.item_name + ':' + item.description + ':' + item.price + ':' + item.email;
		if (i < itlist.size() - 1)
		{
			result.response = result.response + ',';
		}
		i++;
	}
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::uploadItem(RequestInfo requestInfo)
{
	SqliteDatabase db;
	std::string stringBuffer(requestInfo.buffer.begin(), requestInfo.buffer.end()); //converts char buffer to std::string
	JsonRequestPacketDeserializer jsonDeserialize;
	UploadItemRequest request = jsonDeserialize.deserializeUploadItemRequest(stringBuffer);
	//std::list<Item> itlist = db.getItems(); Dont think im supposed to do checks here.
	db.uploadItem(request.userName, request.itemName, request.description, request.price, request.email);
	RequestResult result;
	result.response = "Success!";
	result.newHandler = this;
	return result;
}
