#include "UnitLogic.h"

UnitLogic::UnitLogic(UnitTypes type)
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);

	this->type = type;

	switch(type)
	{
		case UnitTypes::LIGHT:	
		{
			this->attackpower = 3;
			this->range = 2;
			break;
		}
		case UnitTypes::HEAVY:	
		{
			this->attackpower = 6;
			this->range = 3;
			break;
		}
		case UnitTypes::LONGRANGE:	
		{
			this->attackpower = 9;
			this->range = 1;
			break;
		}
		case UnitTypes::ARTILLERY:
		{
			this->attackpower = 300;
			this->range = 1;
			break;
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
