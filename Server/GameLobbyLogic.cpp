#include "GameLobbyLogic.h"

GameLobbyLogic::GameLobbyLogic(short id, User* master)
{
	this->server = Server::get();
	this->id = id;
	this->gameMaster = master;

	server->newMessageCallback.push_back(LogicMessageCallback);
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

void GameLobbyLogic::LogicMessageCallback(SOCKET s,short id,vector<char> data)
{
	switch(id)
	{
	case 0x0300:
		{
			
		}break;
	case 0x0303:
		{
			
		}break;
	case 0x0310:
		{
			
		}break;
	case 0x0311:
		{
			
		}break;
	}

}

//  00:	Client -> Server (disconnect request)
//	01:	Server -> Client (disconnect – keine Daten)
//	02: Server -> Client (Vektor connected Players)
//	03:	Client -> Server (Start – Game – Nur Master)
//	04:	Server -> Client (Im Spiel)
//	10:	Client -> Server (Mapchange)
//	11:	Client -> Server (max. Anzahl Spieler change)
//	20:	Server -> Client (ack 10)
//	21:	Server -> Client (ack 11)
