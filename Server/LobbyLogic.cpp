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
	server->deleteFromNewMessageCallback(this);
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
				//Zudem müsste ihr hier mal die Größe dieser Datei mit schicken. Der Client hat keine Ahnung wie lang so ne Lobby is
				erfg.push_back(it->first);//ToDo wieso habt ihr eine map<short   wenn ihr das sowieso später zu nem char macht?
				erfg.push_back(it->second->getID());
				erfg.push_back(it->second->getPlayerlimit());

				string master = it->second->getGamemaster()->getName();
				for (unsigned int i = 0; i < master.length(); i++)
					erfg.push_back(master[i]);

				//noch die spieler vom game pushen
			}

			server->write(s, 0x0200,erfg);

			break;
		}
		//	02:		Client -> Server (will zu Spiellobby connecten)
		//	03: 	Server -> Client (connect Bestätigung)
	case 0x0202:
		{
			// gameid aus daten lesen, den user da reinschreiben

			erfg.push_back(1);
			server->write(s, 0x0203, erfg);
			break;
		}
		//	04:		Client -> Server (will Spiellobby erstellen)
		//	05: 	Server -> Client (erstellen Bestätigung)
	case 0x0204:
		{

			erfg.push_back(1);
			server->write(s, 0x0205, erfg);
			break;
		}
	}
}

void LobbyLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
}