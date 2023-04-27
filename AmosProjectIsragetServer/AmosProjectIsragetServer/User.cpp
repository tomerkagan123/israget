#include "User.h"

User::User(const std::string& password, const std::string& name, const std::string& mail)
{
	this->m_name = name;
	this->m_mail = mail;
	this->m_password = password;
}

const std::string& User::getPassword() const
{
	return this->m_password;
}
