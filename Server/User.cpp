#include "User.h"

User::User()
{
	this->name = "";
}

User::User(string name)
{
	this->name = name;
}

User::~User()
{

}

string User::getName()
{
	return this->name;
}

void User::setName(string name)
{
	this->name = name;
}