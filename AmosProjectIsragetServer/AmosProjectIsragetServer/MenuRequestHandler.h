#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory; //forward declaration
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RequestHandlerFactory* reqHandlerFactory);
	virtual bool isRequestRelevant(RequestInfo requestInfo) const override;
	virtual RequestResult handleRequest(RequestInfo requestInfo) override;
private:
	LoggedUser m_user;
	RequestHandlerFactory* m_handlerFactory;
	RequestResult signout(RequestInfo requestInfo);
	RequestResult getItems(RequestInfo requestInfo);
	RequestResult getSpecItems(RequestInfo requestInfo);
	RequestResult uploadItem(RequestInfo requestInfo);
};