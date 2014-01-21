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
	server->addToErrorCallback(this);
}

LobbyLogic::~LobbyLogic()
{
	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
	for (std::map<short,GameLobbyLogic*>::iterator it=this->gamesCreated.begin(); it!=this->gamesCreated.end(); ++it)
		delete it->second;
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
		
			for (map<short, GameLobbyLogic*>::iterator it = gamesCreated.begin(); it != gamesCreated.end(); it++)
			{
				if (it->second->getPlayers().size() == 0)
				{
					gamesCreated.erase(it);
				}
				else
				{
					std::vector<char> tmp;

					//erfg.push_back(it->first);

					tmp = code(it->first);
					erfg.push_back(tmp[0]);
					erfg.push_back(tmp[1]);


					tmp = code(it->second->getPlayerlimit());
					erfg.push_back(tmp[0]);
					erfg.push_back(tmp[1]);

					string gamelobbyname = it->second->getName();
					short len = gamelobbyname.length();
					tmp = code(len);
					erfg.push_back(tmp[0]);
					erfg.push_back(tmp[1]);

					tmp = code(gamelobbyname);
					for (unsigned int i = 0; i < tmp.size(); i++)
							erfg.push_back(tmp[i]);
				
					string master = it->second->getGamemaster().Name;
					len = master.length();
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
			}
							
			server->write(s, 0x0200,erfg);

			break;
			}


		//	02:		Client -> Server (will zu Spiellobby connecten)
		//	03: 	Server -> Client (connect Bestätigung)
		case 0x0202:
			{
				// gameid aus daten lesen, den user da reinschreiben
				short mapid = data[0];

				for (unsigned int i = 0; i < server->connectedPlayers.size(); i++)
					if (server->connectedPlayers[i].s == s && gamesCreated[mapid]->isAlreadyConnected(s) == false)
					{
							gamesCreated[mapid]->addPlayer(&server->connectedPlayers[i]);
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
				//data: string gamename auslesen TODO! id aus gamelobbylogic entfernen
				static short id = 0;
				id++;
				string gamename;

				short len = decodeShort(data, 0);
				gamename = decodeString(data, 2, len);

				PlayerData requester;
				for (unsigned int i = 0; i < server->connectedPlayers.size(); i++)
					if (server->connectedPlayers[i].s == s)
					{
						requester = server->connectedPlayers[i];
					}
				
					if(!requester.isGamemaster)
					{
						GameLobbyLogic* GameLobby = new GameLobbyLogic(id, requester, gamename);

						std::map<short, GameLobbyLogic*>::iterator it = this->gamesCreated.begin();
						this->gamesCreated.insert (it, std::pair<short, GameLobbyLogic*>(id,GameLobby));
			
						for (unsigned int i = 0; i < server->connectedPlayers.size(); i++)
						if (server->connectedPlayers[i].s == s)
						{
							server->connectedPlayers[i].isGamemaster = true;
						}

						erfg.push_back(1);
						server->write(s, 0x0205, erfg);
					}
					else
					{
						erfg.push_back(0);
						server->write(s, 0x0205, erfg);
					}
				break;
			}
	}
}

void LobbyLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
	switch (errCode)
	{
		case 0x0010:
			{
				for(int i = 0; i < (signed) server->connectedPlayers.size(); i++)
				{
					if(s == server->connectedPlayers[i].s)
						server->connectedPlayers.erase(server->connectedPlayers.begin() + i);
				}
			}break;
		case 0x0011:
			{
				for(int i = 0; i < (signed) server->connectedPlayers.size(); i++)
				{
					if(s == server->connectedPlayers[i].s)
						server->connectedPlayers.erase(server->connectedPlayers.begin() + i);
				}
			}break;
	}
}