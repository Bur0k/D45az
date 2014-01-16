#include "GameLogic.h"

GameLogic::GameLogic()
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);
}

GameLogic::~GameLogic()
{
	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
}

void GameLogic::processNewMessage(SOCKET s,short id,std::vector<char> data)
{
	switch(id)
	{
	case 0x0400:
		{

		}
	}
}
	
void GameLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{

}