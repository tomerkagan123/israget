#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "sqlite3.h"
#include <iostream>

int callbackGetUsers(void* data, int argc, char** argv, char** azColName);
int callbackGetNumberFromColumn(void* data, int argc, char** argv, char** azColName);
int callbackGetTimeFromColumn(void* data, int argc, char** argv, char** azColName);
int callbackVecStats(void* data, int argc, char** argv, char** azColName);
int callbackGetItems(void* data, int argc, char** argv, char** azColName);

#endif 