#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <vector>
#include "Item.h"
#include <list>
//#include "Server.h"
class SqliteDatabase : public IDatabase
{
public:
	bool doesUserExist(std::string name) override;
	bool doesPasswordMatch(std::string name, std::string password) override;
	void addNewUser(std::string name, std::string password, std::string email) override;
	void uploadItem(std::string userName, std::string itemName, std::string description, std::string price, std::string email);
	void deleteItem(std::string userName, std::string itemName, std::string description);
	std::list<Item> getItems();
	std::list<Item> getSpecItems(std::string name);
	SqliteDatabase();
	~SqliteDatabase();

private:
	sqlite3* m_db;
	void open();
	void close();
};