#include "IRequestHandler.h"

bool IRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	return false;
}
RequestResult IRequestHandler::handleRequest(RequestInfo requestInfo)
{
	return RequestResult();
}
