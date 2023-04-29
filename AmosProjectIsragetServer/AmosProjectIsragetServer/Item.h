#pragma once
#include <iostream>

class Item
{
public:
	std::string user_name;
	std::string item_name;
	std::string description;
	std::string email;
	std::string price;
	Item(std::string user_name, std::string item_name, std::string description, std::string price, std::string email)
	{
		this->user_name = user_name;
		this->item_name = item_name;
		this->description = description;
		this->price = price;
		this->email = email;
	}
};