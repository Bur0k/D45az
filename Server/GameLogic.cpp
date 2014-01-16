#include "GameLogic.h"

GameLogic::GameLogic(vector<PlayerData*> players)
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);

	for(unsigned int i = 0; i < players.size(); i++)
		IngameLogic* ingame = new IngameLogic(players[i]);
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