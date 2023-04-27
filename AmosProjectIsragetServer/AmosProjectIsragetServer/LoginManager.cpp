#include "LoginManager.h"

void LoginManager::signup(const std::string& name, const std::string& password, const std::string& email)
{
	this->m_database->addNewUser(name, password, email);
}

bool LoginManager::login(const std::string& name, const std::string& password)
{
	bool tOrF = this->m_database->doesPasswordMatch(name, password);
	if (!tOrF)
	{
		std::cerr << "Either user doesnt exist or password doesnt match. Try again." << std::endl;
		return false;
	}
	LoggedUser user(name);
	if (std::find(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), user) != this->m_loggedUsers.end())
	{
		std::cerr << "Already logged in." << std::endl;
		return false;
	}
	this->m_loggedUsers.push_back(user);
	return true;
}

void LoginManager::logout(const std::string& name)
{
	int i = 0;
	int index = -1;
	for (LoggedUser user : this->m_loggedUsers)
	{
		if (user.getName() == name)
			index = i;
		if (index != -1)
		{
			this->m_loggedUsers.erase(this->m_loggedUsers.begin() + index);
			std::cout << "Logged out!" << std::endl;
			return;
		}
		i++;
	}
	std::cout << "You shouldnt see this, error! couldnt logout!" << std::endl;
}

LoginManager::LoginManager()
{
	this->m_database = new SqliteDatabase();
}
