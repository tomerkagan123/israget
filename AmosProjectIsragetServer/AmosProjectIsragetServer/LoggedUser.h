#pragma once
#include <string>
#include <iostream>

class LoggedUser
{
public:
	LoggedUser();
	LoggedUser(const std::string& name);
	const std::string& getName() const;
	bool operator== (LoggedUser other);
private:
	std::string m_name;
};
