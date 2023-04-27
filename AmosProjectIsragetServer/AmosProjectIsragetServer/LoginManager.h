#pragma once
#include <string>
#include <iostream>
#include "SqliteDatabase.h"
#include "LoggedUser.h"
#include <vector>

class LoginManager
{
public:
	void signup(const std::string &name, const std::string &password, const std::string &email);
	bool login(const std::string& name, const std::string& password);
	void logout(const std::string& name);
	LoginManager();

private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
