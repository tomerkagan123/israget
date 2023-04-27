#include "SqliteDatabase.h"
#include "User.h"
#include "functions.h"
#include "sqlite3.h"
#include <list>
#include <vector>

/*
* Gets a name and checks if the user exists
* Input: name of user
* Output: True/False if user exists
*/
bool SqliteDatabase::doesUserExist(std::string name)
{
	std::string sqlStatement = "SELECT * FROM USERS WHERE USER_NAME = '" + name + "';";
	std::list<User> list;
	int res = sqlite3_exec(this->m_db, sqlStatement.c_str(), callbackGetUsers, &list, nullptr);
	if (list.empty())
		return false;
	return true;
}

/*
* Gets a user and password and compares it to the password
* saved in the database
* Input: name and password
* Output: True/False if matches or not
*/
bool SqliteDatabase::doesPasswordMatch(std::string name, std::string password)
{
	std::string sqlStatement = "SELECT * FROM USERS WHERE USER_NAME = '" + name + "';";
	std::list<User> list;
	int res = sqlite3_exec(this->m_db, sqlStatement.c_str(), callbackGetUsers, &list, nullptr);
	if (list.empty())
	{
		std::cout << "user doesnt exist!" << std::endl;
		return false;
	}
	if (list.front().getPassword() == password)
	{
		std::cout << "Passwords match!" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Passwords don't match." << std::endl;
		return false;
	}

}

/*
* Adds new user to the SQL Database
* Input: name, password, email of specific user wanting to be added
* Output: Adds user if arguments fit the criteria
*/

void SqliteDatabase::addNewUser(std::string name, std::string password, std::string email)
{
	std::string sqlStatement = "INSERT INTO USERS VALUES('" + name + "','" + password +"','" + email + "'); ";
	int res = sqlite3_exec(this->m_db , sqlStatement.c_str() , nullptr , nullptr , nullptr);
	if (res != SQLITE_OK)
		std::cerr << "Error." << std::endl;
}

/*
* Constructor
*/
SqliteDatabase::SqliteDatabase()
{
	open();
}

/*
* Destructor
*/
SqliteDatabase::~SqliteDatabase()
{
	close();
}

/*
* Closes connection to SQL Database
*/
void SqliteDatabase::close()
{
	sqlite3_close(this->m_db);
	this->m_db = nullptr;
}


/*
* Opens connection to SQL Database
*/
void SqliteDatabase::open()
{
	std::string dbFileName = "israget.sqlite";
	int res = sqlite3_open(dbFileName.c_str(), &this->m_db);
	if (res != SQLITE_OK)
	{
		this->m_db = nullptr;
		std::cerr << "Failed to open DB" << std::endl;
	}
}

