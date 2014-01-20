#include "CityLogic.h"

CityLogic::CityLogic(short id, short x, short y)
{
	this->server = Server::get();

	this->id = id;
	this->posX = x;
	this->posY = y;
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

void CityLogic::processNewMessage(SOCKET s,short id,std::vector<char> data)
{
	switch(id)
	{

	}
}

void CityLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
	switch(errCode)
	{

	}
}