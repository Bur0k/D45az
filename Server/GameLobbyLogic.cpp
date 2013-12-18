#include "GameLobbyLogic.h"

GameLobbyLogic::GameLobbyLogic(short id, User* master)
{
	this->id = id;
	this->gameMaster = master;

	//Message Callback Anmelden nicht vergessen!
}

GameLobbyLogic::~GameLobbyLogic()
{
}

void GameLobbyLogic::setID(short id)
{
	this->id = id;
}

short GameLobbyLogic::getID()
{
	return this->id;
}

void GameLobbyLogic::setPlayerlimit(short limit)
{
	this->playerlimit = limit;
}

short GameLobbyLogic::getPlayerlimit()
{
	return this->playerlimit;
}

void GameLobbyLogic::setGamemaster(User* player)
{
	this->gameMaster = player;
}

User* GameLobbyLogic::getGamemaster()
{
	return this->gameMaster;
}

/*
void GameLobbyLogic::setMap(Map map)
{
	this->currentMap = map;
}

Map GameLobbyLogic::getMap()
{
	return this->currentMap;
}
*/
	
