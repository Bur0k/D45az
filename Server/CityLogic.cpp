#include "CityLogic.h"

CityLogic::CityLogic(short id, short x, short y)
{
	this->server = Server::get();

	this->id = id;
	this->position = new POINT();
	this->position->x = x;
	this->position->y = y;
	
	this->level = 1;
	this->generatedIncome = 500;

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);
}

CityLogic::~CityLogic()
{
	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
}

void CityLogic::upgradeCity()
{
	if(this->level <= 5)
	{
		this->level++;
		this->generatedIncome += 500;
	}
}

void CityLogic::processNewMessage(SOCKET s,short id,std::vector<char> data)
{
}

void CityLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
}