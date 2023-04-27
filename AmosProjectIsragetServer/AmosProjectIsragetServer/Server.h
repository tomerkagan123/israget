#pragma once
#include "Communicator.h"
#include "SqliteDatabase.h"
class Server
{
public:
	void run();
private:
	Communicator m_communicator;
	IDatabase* m_database;
};