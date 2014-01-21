#include "GameLobbyLogic.h"

GameLobbyLogic::GameLobbyLogic(short id, PlayerData master, string GameLobbyName)
{
	this->server = Server::get();

	//this->id = id;
	this->gameMaster = master;
	this->playerlimit = 4;
	this->players.push_back(&this->gameMaster);
	this->gameLobbyName = GameLobbyName;

	Map* map = new Map();
	map->load("Data/Maps/TestMap.tmx");
	this->currentMap = map;

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);
}

GameLobbyLogic::~GameLobbyLogic()
{
	delete this->currentMap;

	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
}

/* GETTER - SETTER */

void GameLobbyLogic::setName(string name)
{
	 this->gameLobbyName = name;
}

string GameLobbyLogic::getName()
{
	return this->gameLobbyName;
}

//void GameLobbyLogic::setID(short id)
//{
//	this->id = id;
//}
//
//short GameLobbyLogic::getID()
//{
//	return this->id;
//}

void GameLobbyLogic::setPlayerlimit(short limit)
{
	this->playerlimit = limit;
}

short GameLobbyLogic::getPlayerlimit()
{
	return this->playerlimit;
}

void GameLobbyLogic::setGamemaster(PlayerData player)
{
	this->gameMaster = player;
}

PlayerData GameLobbyLogic::getGamemaster()
{
	return this->gameMaster;
}

vector<PlayerData*>& GameLobbyLogic::getPlayers()
{
	return this->players;
}


void GameLobbyLogic::setMap(Map* map)
{
	this->currentMap = map;
}

Map* GameLobbyLogic::getMap()
{
	return this->currentMap;
}


/* Funktionen */

void GameLobbyLogic::addPlayer(PlayerData* player)
{
	if(this->players.size() < this->playerlimit)
		this->players.push_back(player);
}

bool GameLobbyLogic::isAlreadyConnected(SOCKET s)
{
	for(int i = 0; i < this->players.size(); i++)
	{
		if(this->players[i]->s == s)
			return true;
	}

	return false;
}

void GameLobbyLogic::sendPlayerNames(SOCKET s)
{
	std::vector<char> erfg;

	for(int i = 0; i < (signed) this->players.size(); i++)
	{
		string name = this->players[i]->Name;
		vector<char> tmp = code(name);

		erfg.insert(erfg.end(), tmp.begin(), tmp.end());
		erfg.push_back('/');
		
		//if( i == (this->players.size() - 1))
		//	erfg.push_back('/');
	}

	this->server->write(s, 0x0302, erfg);
}

void GameLobbyLogic::sendMaxPlayers(SOCKET s)
{
	vector<char> erfg = code(this->playerlimit);
	this->server->write(s, 0x0305, erfg);
}

void GameLobbyLogic::sendGameMaster(SOCKET s)
{
	vector<char> erfg = code(this->gameMaster.Name);
	this->server->write(s, 0x0306, erfg);
}

void GameLobbyLogic::sendGameLobbyData(SOCKET s)
{

}
//void GameLobbyLogic::sendCurrentMap(SOCKET s)
//{
//	vector<char> erfg = code(this->currentMap->id);
//	this->server->write(s, 0x0306, erfg);
//}

/* Kommunikation */

void GameLobbyLogic::processNewMessage(SOCKET s,short id,vector<char> data)
{
	bool socketAvailable = false;

	for(int i = 0; i < (signed) this->players.size(); i++)
	{
		if(s == this->players[i]->s)
			socketAvailable = true;
	}

	if(socketAvailable)
	{
		switch(id)
		{
		case 0x0300:
			{
				for(unsigned int i = 0; i < this->players.size(); i++)
					if(this->players[i]->s == s)
						this->players.erase(this->players.begin() + i);
				
				std::vector<char> erfg;

				this->server->write(s, 0x0301, erfg);	
			}break;
		case 0x0303:
			{
				if(this->gameMaster.s == s)
				{
					// Spielstart

					GameLogic* game = new GameLogic(this->players, this->currentMap);

					std::vector<char> erfg;

					this->server->write(s, 0x0304, erfg);
				}
			}break;
		case 0x0310:
			{
				if(this->gameMaster.s == s)
				{
					short map = data[0] - 48;

					// Mapchange

					std::vector<char> erfg;

					this->server->write(s, 0x0320, erfg);
				}
			}break;
		case 0x0311:
			{
				if(this->gameMaster.s == s)
				{
					short anz = data[0];

					if(anz > 4)
						anz = 4;

					this->setPlayerlimit(anz);

					std::vector<char> erfg;
					char playerCount = anz;
					erfg.push_back(playerCount);
					this->server->write(s, 0x0321, erfg);
				}
		case 0x0330:

			{
				this->sendGameMaster(s);
				this->sendMaxPlayers(s);
				this->sendPlayerNames(s);
				//this->sendCurrentMap(s);
			}
			}break;
		}
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
	switch (errCode)
	{
		case 0x0010:
			{
				for(int i = 0; i < (signed) this->players.size(); i++)
				{
					if(s == this->players[i]->s)
					{
						if(this->players[i]->s == this->gameMaster.s)
							if(this->players.size() != 1)
							{
								this->setGamemaster(*this->players[i + 1]);
							}
				
						this->players.erase(this->players.begin() + i);	
					}
				}
			}break;
		case 0x0011:
			{
				for(int i = 0; i < (signed) this->players.size(); i++)
				{
					if(s == this->players[i]->s)
					{
						if(this->players[i]->s == this->gameMaster.s)
							if(this->players.size() != 1)
							{
								this->setGamemaster(*this->players[i + 1]);
							}
				
						this->players.erase(this->players.begin() + i);	
					}
				}
			}break;
	}
}