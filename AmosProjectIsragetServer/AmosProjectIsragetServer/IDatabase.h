#pragma once
#include <iostream>
#include <vector>
class IDatabase
{
public:
	virtual bool doesUserExist(std::string name)=0;
	virtual bool doesPasswordMatch(std::string name, std::string password)=0;
	virtual void addNewUser(std::string name, std::string password, std::string email) = 0;
	/*virtual std::string getPlayerAverageAnswerTime(std::string name) = 0;
	virtual int getNumOfCorrectAnswers(std::string name)=0;
	virtual int getNumOfTotalAnswers(std::string name)=0;
	virtual int getNumOfPlayerGames(std::string name)=0;
	virtual int updatePlayerStatistics(std::string newTime, std::string value, std::string name)=0;
	virtual std::vector<std::string> getEverybodyStats() = 0;*/
};