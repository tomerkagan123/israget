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

void SqliteDatabase::uploadItem(std::string userName, std::string itemName, std::string description, std::string price, std::string email)
{
	std::string sqlStatement = "INSERT INTO ITEMS VALUES('" + userName + "','" + itemName + "','" + description + "','" + price + "','" + email + "'); ";
	int res = sqlite3_exec(this->m_db, sqlStatement.c_str(), nullptr, nullptr, nullptr);
	if (res != SQLITE_OK)
		std::cerr << "Error." << std::endl;
}

void SqliteDatabase::deleteItem(std::string userName, std::string itemName, std::string description)
{
	std::string sqlStatement = "DELETE FROM ITEMS WHERE user_name = '" + userName + "' AND item_name = '" + itemName + "' AND description = '" + description + "'; ";
	int res = sqlite3_exec(this->m_db, sqlStatement.c_str(), nullptr, nullptr, nullptr);
	if (res != SQLITE_OK)
		std::cerr << "Error." << std::endl;
}

std::list<Item> SqliteDatabase::getItems()
{
	std::string sqlStatement = "SELECT * FROM ITEMS;";
	std::list<Item> list;
	int res = sqlite3_exec(this->m_db, sqlStatement.c_str(), callbackGetItems, &list, nullptr);
	if (res != SQLITE_OK)
		std::cerr << "Error." << std::endl;
	return list;
}
std::list<Item> SqliteDatabase::getSpecItems(std::string name)
{
	std::cout << name << std::endl;
	std::string sqlStatement = "SELECT * FROM ITEMS WHERE item_name LIKE '" + name + "'; ";
	std::list<Item> list;
	int res = sqlite3_exec(this->m_db, sqlStatement.c_str(), callbackGetItems, &list, nullptr);
	if (res != SQLITE_OK)
		std::cerr << "Error." << std::endl;
	return list;
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

