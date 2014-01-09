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
				//Zudem müsste ihr hier mal die Größe dieser Datei mit schicken. Der Client hat keine Ahnung wie lang so ne Lobby is
				//muss ich net
				erfg.push_back(it->first >> 8);
				erfg.push_back(it->first &0xFF);

				erfg.push_back(it->second->getID() << 8);
				erfg.push_back(it->second->getID() & 0xFF);

				erfg.push_back(it->second->getPlayerlimit() << 8);
				erfg.push_back(it->second->getPlayerlimit() & 0xFF);
				
				
				string master = it->second->getGamemaster()->Name;
				short len = master.length();
				erfg.push_back(len << 8);
				erfg.push_back(len & 0xFF);
				for (unsigned int i = 0; i < master.length(); i++)
						erfg.push_back(master[i]);

				
				for (unsigned int i = 0; i < it->second->getPlayers().size(); i++)
				{
					string name = it->second->getPlayers().at(i)->Name;
					len = name.length();
					erfg.push_back(len << 8);
					erfg.push_back(len & 0xFF);
					for (unsigned int i = 0; i < name.length(); i++)
						erfg.push_back(name[i]);
				}
			}
							
			server->write(s, 0x0200,erfg);

			break;
			}


		//	02:		Client -> Server (will zu Spiellobby connecten)
		//	03: 	Server -> Client (connect Bestätigung)
		case 0x0202:
			{
				// gameid aus daten lesen, den user da reinschreiben
				char mapid = data[0];

				for (unsigned int i = 0; i < connectedPlayers.size(); i++)
					if (connectedPlayers[i].s == s)
						//add player von stefan
						//gamesCreated[mapid]->addPlayer;
							//break;
				

				

				erfg.push_back(1);
				server->write(s, 0x0203, erfg);
				break;
			}
		//	04:		Client -> Server (will Spiellobby erstellen)
		//	05: 	Server -> Client (erstellen Bestätigung)
		case 0x0204:
			{
				//data: string username, auslesen
				short id = 0;
				string name = "";

				
				//while (gamesCreated.count(id) == 1)
				//	id++;

				id = gamesCreated.size();

				for (unsigned int i = 0; i < data.size(); i++) 
					name += data[i];

				PlayerData requester;
				for (unsigned int i = 0; i < connectedPlayers.size(); i++)
					if (connectedPlayers[i].Name == name)
					{
						requester = connectedPlayers[i];
						break;
					}
				
				GameLobbyLogic* GameLobby = new GameLobbyLogic(id, &requester);
				
				erfg.push_back(1);
				server->write(s, 0x0205, erfg);
				break;
			}
	}
}

void LobbyLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
}