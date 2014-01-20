#include "UnitLogic.h"

UnitLogic::UnitLogic(short type)
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);

	switch(type)
	{
		case 1:	//Infantry
		{
			this->attackpower = 3;
			this->range = 2;
		}
		case 2:	//Cavalry
		{
			this->attackpower = 6;
			this->range = 3;
		}
		case 3:	//Artillery
		{
			this->attackpower = 9;
			this->range = 1;
		}
	}
}

UnitLogic::~UnitLogic()
{
	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
}

void UnitLogic::processNewMessage(SOCKET s,short id,std::vector<char> data)
{
	switch(id)
	{

	}
}

void UnitLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
	switch(errCode)
	{

	}
}
