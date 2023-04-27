#include "LoggedUser.h"

LoggedUser::LoggedUser()
{
	this->m_name = "default";
}

LoggedUser::LoggedUser(const std::string& name)
{
	this->m_name = name;
}

const std::string& LoggedUser::getName() const
{
	return this->m_name;
}

bool LoggedUser::operator==(LoggedUser other)
{
	return this->getName() == other.getName();
}

