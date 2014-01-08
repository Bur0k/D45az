#include "GameLobbyLogic.h"

GameLobbyLogic::GameLobbyLogic(short id, User* master)
{
	this->server = Server::get();
	this->id = id;
	this->gameMaster = master;

	server->addToNewMessageCallback(this);
}

GameLobbyLogic::~GameLobbyLogic()
{
	server->deleteFromNewMessageCallback(this);
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

void GameLobbyLogic::processNewMessage(SOCKET s,short id,vector<char> data)
{
	switch(id)
	{
	case 0x0300:
		{
			string name = "";

			//testen
			for (unsigned int i = 0; i < data.size(); i++) 
				name += data[i];

			for(unsigned int i = 0; i < this->players.size(); i++)
				if(this->players[i]->getName() == name)
					this->players.erase(this->players.begin() + i, this->players.begin() + i);
				
			std::vector<char> erfg;

			this->server->write(s, 0x0301, erfg);	
		}break;
	case 0x0303:
		{
			string name = "";

			//testen
			for (unsigned int i = 0; i < data.size(); i++) 
				name += data[i];

			if(name == this->gameMaster->getName)
			{
				// Spielstart

				std::vector<char> erfg;

				this->server->write(s, 0x0304, erfg);
			}
		}break;
	case 0x0310:
		{
			short map = data[0] - 48;

			// Mapchange

			std::vector<char> erfg;

			this->server->write(s, 0x0320, erfg);
		}break;
	case 0x0311:
		{
			short anz = data[0] - 48;

			this->setPlayerlimit(anz);

			std::vector<char> erfg;

			this->server->write(s, 0x0321, erfg);
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




void GameLobbyLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
}