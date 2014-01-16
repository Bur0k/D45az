#include "IngameLogic.h"

IngameLogic::IngameLogic(PlayerData* owner)
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);

	this->owner = owner;
}

IngameLogic::~IngameLogic()
{
	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
}

void IngameLogic::processNewMessage(SOCKET s,short id,std::vector<char> data)
{
	switch(id)
	{
	case 0x0400:
		{

		}
	}
}
	
void IngameLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{

}