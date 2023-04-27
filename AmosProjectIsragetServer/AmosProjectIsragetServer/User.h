#pragma once
#include <string>
#include <iostream>

class User
{
public:

	User(const std::string& password, const std::string& name, const std::string& mail);

	//const std::string& getName() const;
	//void setName(const std::string& name);

	const std::string& getPassword() const;
	//void setPassword(const std::string& name);

	//const std::string& getMail() const;
	//void setMail(const std::string& name)


private:
	std::string m_password;
	std::string m_name;
	std::string m_mail;
};
