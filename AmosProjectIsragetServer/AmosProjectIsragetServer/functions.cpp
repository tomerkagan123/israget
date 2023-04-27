#include "functions.h"
#include <list>
#include "User.h"
#include "sqlite3.h"
#include <vector>
#include "Item.h"
/*
* Callback to sqlite3_exec, returns a list with all the users
*/
int callbackGetUsers(void* data, int argc, char** argv, char** azColName)
{
	std::list<User>* uslist = (std::list<User>*)data;
	std::string password;
	std::string mail;
	std::string name;
	for (int i = 0; i < argc; i++)
	{
		if ((std::string)azColName[i] == "email")
		{
			mail = argv[i];
		}
		else if ((std::string)azColName[i] == "user_name")
		{
			name = argv[i];
		}
		else if ((std::string)azColName[i] == "password")
		{
			password = argv[i];
		}
	}
	User user(password, name, mail);
	uslist->push_back(user);
	return 0;
}

int callbackGetItems(void* data, int argc, char** argv, char** azColName)
{
	std::list<Item>* itlist = (std::list<Item>*)data;
	std::string user_name;
	std::string item_name;
	std::string email;
	std::string description;
	unsigned int price = 0;
	for (int i = 0; i < argc; i++)
	{
		if ((std::string)azColName[i] == "email")
		{
			email = argv[i];
		}
		else if ((std::string)azColName[i] == "user_name")
		{
			user_name = argv[i];
		}
		else if ((std::string)azColName[i] == "description")
		{
			description = argv[i];
		}
		else if ((std::string)azColName[i] == "price")
		{
			price = std::stoi(argv[i]);
		}
		else if ((std::string)azColName[i] == "item_name")
		{
			item_name = argv[i];
		}
	}
	Item item(user_name,item_name,description, price, email);
	itlist->push_back(item);
	return 0;
}

int callbackGetNumberFromColumn(void* data, int argc, char** argv, char** azColName)
{
	int* num = reinterpret_cast<int*>(data);
	*num = atoi(argv[0]);
	return 0;
}

int callbackGetTimeFromColumn(void* data, int argc, char** argv, char** azColName)
{
	std::string* num = reinterpret_cast<std::string*>(data);
	*num = argv[0];
	return 0;
}

int callbackVecStats(void* data, int argc, char** argv, char** azColName)
{
	std::vector<std::string>* vec = reinterpret_cast<std::vector<std::string>*>(data);
	std::string name;
	int games = 0;
	int totalans = 0;
	int correctans = 0;
	std::string avgtime;
	for (int i = 0; i < argc; i++)
	{
		if ((std::string)azColName[i] == "user_name")
		{
			name = argv[i];
		}
		else if ((std::string)azColName[i] == "total_answers")
		{
			totalans = atoi(argv[i]);
		}
		else if ((std::string)azColName[i] == "correct_answers")
		{
			correctans = atoi(argv[i]);
		}
		else if ((std::string)azColName[i] == "total_games")
		{
			games = atoi(argv[i]);
		}
		else if ((std::string)azColName[i] == "avg_time")
		{
			avgtime = argv[i];
		}
	}
	std::string str ="Name : " + name  + ", correctAnswers : " + std::to_string(correctans) + ", totalAnswers : " + std::to_string(totalans) + ", playerGames : " + std::to_string(games) + ", averageAnswerTime : " + avgtime;
	vec->push_back(str);
	return 0;
}