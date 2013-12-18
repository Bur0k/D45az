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
	//Message Callback Anmelden nicht vergessen!
}

LobbyLogic::~LobbyLogic()
{
}

void LobbyLogic::LobbyLogicMessageCallback(ClientHandler* ch,short id,vector<char> data)
{
	switch (id)
	{
		//	00: 	Server -> Client (sendet Lobby-Daten)
		//	01: 	Client -> Server (fordert Lobby-Daten an)
		case 0x0201:
			{
				std::vector<char> erfg;
				for (map<short, GameLobbyLogic*>::iterator it = this->gamesCreated.begin(); it != this->gamesCreated.end; it++)
				{
					erfg.push_back(it->first);
					erfg.push_back(it->second->getID);
					erfg.push_back(it->second->getPlayerlimit);
					
					string master = it->second->getGamemaster;
					for (int i = 0; i < master.length; i++)
						erfg.push_back(master[i]);

					//noch die spieler vom game pushen
				}
							
				ch->write(0x0200,erfg);

				break;
			}
		//	02:		Client -> Server (will zu Spiellobby connecten)
		//	03: 	Server -> Client (connect Bestätigung)
		case 0x0202:
			{
				break;
			}
		//	04:		Client -> Server (will Spiellobby erstellen)
		//	05: 	Server -> Client (erstellen Bestätigung)
		case 0x0204:
			{
				break;
			}
	}
}