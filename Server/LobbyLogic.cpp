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

				std::vector<char> tmp;

				erfg.push_back(it->first);


				tmp = code(it->second->getID());
				erfg.push_back(tmp[0]);
				erfg.push_back(tmp[1]);


				tmp = code(it->second->getPlayerlimit());
				erfg.push_back(tmp[0]);
				erfg.push_back(tmp[1]);
				
				string master = it->second->getGamemaster()->Name;
				short len = master.length();
				tmp = code(len);
				erfg.push_back(tmp[0]);
				erfg.push_back(tmp[1]);

				tmp = code(master);
				for (unsigned int i = 0; i < tmp.size(); i++)
						erfg.push_back(tmp[i]);

				short countplayers = it->second->getPlayers().size();
				tmp = code(countplayers);
				erfg.push_back(tmp[0]);
				erfg.push_back(tmp[1]);

				
				for (unsigned int i = 0; i < it->second->getPlayers().size(); i++)
				{
					string name = it->second->getPlayers().at(i)->Name;
					len = name.length();
					tmp = code(len);
					erfg.push_back(tmp[0]);
					erfg.push_back(tmp[1]);

					tmp = code(name);
					for (unsigned int i = 0; i < tmp.size(); i++)
						erfg.push_back(tmp[i]);
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
					{
							gamesCreated[mapid]->addPlayer(&connectedPlayers[i]);
							break;
					}			

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


				id = gamesCreated.size();

				PlayerData requester;
				for (unsigned int i = 0; i < connectedPlayers.size(); i++)
					if (connectedPlayers[i].s == s)
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