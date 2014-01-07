#include "LobbyLogic.h"

//	0x02:	Lobby-Logik
//	00: 	Server -> Client (sendet Lobby-Daten)
//	01: 	Client -> Server (fordert Lobby-Daten an)
//	02:		Client -> Server (will zu Spiellobby connecten)
//	03: 	Server -> Client (connect Best�tigung)
//	04:		Client -> Server (will Spiellobby erstellen)
//	05: 	Server -> Client (erstellen Best�tigung)

LobbyLogic::LobbyLogic()
{
	this->server = Server::get();
	server->addToNewMessageCallback(this);
}

LobbyLogic::LobbyLogic(LogInLogic* l)
{
	this->server = Server::get();

	this->LogIn = l;

	server->addToNewMessageCallback(this);
}

LobbyLogic::~LobbyLogic()
{
}

void LobbyLogic::processNewMessage(SOCKET s,short id,vector<char> data)
{
	std::vector<char> erfg;

	switch (id)
	{
		//	00: 	Server -> Client (sendet Lobby-Daten)
		//	01: 	Client -> Server (fordert Lobby-Daten an)
		case 0x0201:
			{
				
			for (map<char, GameLobbyLogic*>::iterator it = gamesCreated.begin(); it != gamesCreated.end(); it++)
				{
				//Zudem m�sste ihr hier mal die Gr��e dieser Datei mit schicken. Der Client hat keine Ahnung wie lang so ne Lobby is
				erfg.push_back(it->first);
				erfg.push_back(it->second->getID());
				erfg.push_back(it->second->getPlayerlimit());
					
				string master = it->second->getGamemaster()->getName();
				for (unsigned int i = 0; i < master.length(); i++)
						erfg.push_back(master[i]);

				//noch die spieler vom game schicken, auf die momentan leider nicht zugegriffen werden kann
				/*
				for (unsigned int i = 0; i < it->second->players.size(); i++)
				{
					string name = it->second->players[i]->getName();
					for (unsigned int i = 0; i < name.length(); i++)
						erfg.push_back(name[i]);
				}*/
			}
							
			server->write(s, 0x0200,erfg);

				break;
			}


		//	02:		Client -> Server (will zu Spiellobby connecten)
		//	03: 	Server -> Client (connect Best�tigung)
		case 0x0202:
			{
				// gameid aus daten lesen, den user da reinschreiben

				erfg.push_back(1);
				server->write(s, 0x0203, erfg);
				break;
			}
		//	04:		Client -> Server (will Spiellobby erstellen)
		//	05: 	Server -> Client (erstellen Best�tigung)
		case 0x0204:
			{
				//data: string username, auslesen
				short id = 0;
				string name = "";
				
				while (gamesCreated.count(id) == 1)
					id++;

				for (unsigned int i = 0; i < data.size(); i++) 
					name += data[i];

				/*User* requester;
				for (unsigned int i = 0; i < LogIn->connectedUsers.size(); i++)
					if (LogIn->connectedUsers[i]->getName == name)
					{
						requester = LogIn->connectedUsers[i];
						break;
					}
				
				GameLobbyLogic* GameLobby = new GameLobbyLogic(id, requester);
				*/
				erfg.push_back(1);
				server->write(s, 0x0205, erfg);
				break;
			}
	}
}

void LobbyLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
}