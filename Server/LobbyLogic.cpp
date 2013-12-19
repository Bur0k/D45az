#include "LobbyLogic.h"

//	0x02:	Lobby-Logik
//	00: 	Server -> Client (sendet Lobby-Daten)
//	01: 	Client -> Server (fordert Lobby-Daten an)
//	02:		Client -> Server (will zu Spiellobby connecten)
//	03: 	Server -> Client (connect Bestätigung)
//	04:		Client -> Server (will Spiellobby erstellen)
//	05: 	Server -> Client (erstellen Bestätigung)

LobbyLogic::LobbyLogic()
{
	self = this;
	this->server = Server::get();

	server->newMessageCallback.push_back(LobbyLogicMessageCallback);
}

LobbyLogic::LobbyLogic(LogInLogic* l)
{
	self = this;
	this->server = Server::get();

	this->LogIn = l;

	server->newMessageCallback.push_back(LobbyLogicMessageCallback);
}

LobbyLogic::~LobbyLogic()
{
	for (map<short, GameLobbyLogic*>::iterator it = self->gamesCreated.begin(); it != self->gamesCreated.end; it++)
	{
		delete(it->second);
	}
}

void LobbyLogic::LobbyLogicMessageCallback(SOCKET s,short id,vector<char> data)
{
	std::vector<char> erfg;

	switch (id)
	{
		//	00: 	Server -> Client (sendet Lobby-Daten)
		//	01: 	Client -> Server (fordert Lobby-Daten an)
		case 0x0201:
			{
				
				for (map<short, GameLobbyLogic*>::iterator it = self->gamesCreated.begin(); it != self->gamesCreated.end; it++)
				{
					erfg.push_back(it->first);
					erfg.push_back(it->second->getID);
					erfg.push_back(it->second->getPlayerlimit);
					
					string master = it->second->getGamemaster;
					for (int i = 0; i < master.length; i++)
						erfg.push_back(master[i]);

					//noch die spieler vom game pushen
				}
							
				self->server->write(s, 0x0200,erfg);

				break;
			}
		//	02:		Client -> Server (will zu Spiellobby connecten)
		//	03: 	Server -> Client (connect Bestätigung)
		case 0x0202:
			{
				// gameid aus daten lesen, den user da reinschreiben

				erfg.push_back(1);
				self->server->write(s, 0x0203, erfg);
				break;
			}
		//	04:		Client -> Server (will Spiellobby erstellen)
		//	05: 	Server -> Client (erstellen Bestätigung)
		case 0x0204:
			{
				//data: string username
				short id = 0;
				string name = "";
				
				while (self->gamesCreated.count(id) == 1)
					id++;

				for (int i = 0; i < data.size(); i++) 
					name += data[i];

				//LogIn->connectedUsers

				//GameLobbyLogic GameLobby = new GameLobbyLogic(id, );

				erfg.push_back(1);
				self->server->write(s, 0x0205, erfg);
				break;
			}
	}
}