//	0x02:	Lobby-Logik
//	00: 	Server -> Client (sendet Lobby-Daten)
//	01: 	Client -> Server (fordert Lobby-Daten an)
//	02:		Client -> Server (will zu Spiellobby connecten)
//	03: 	Server -> Client (connect Bestätigung)
//	04:		Client -> Server (will Spiellobby erstellen)
//	05: 	Server -> Client (erstellen Bestätigung)


#include "Lobby.h"

Lobby::Lobby()
{
	c = Client::get();
	c->addToNewMessageCallback(this);
	updated = false;
	inGameLobby = false;
}

Lobby::~Lobby()
{
	c->deleteFromNewMessageCallback(this);
}

void Lobby::connectToGameLobby(short mapid)
{
	vector<unsigned char> msg;
	vector<unsigned char> tmp = code(mapid);
	msg.push_back(tmp[0]);
	msg.push_back(tmp[1]);

	c->write(0x0202, msg);
}
void Lobby::createNewGameLobby(std::string gamename)
{
	vector<unsigned char> msg;
	vector<unsigned char> tmp;

	tmp = code ((short) gamename.length());
	msg.push_back(tmp[0]);
	msg.push_back(tmp[1]);

	tmp = code(gamename);

	for (unsigned int i = 0; i < gamename.length(); i++)
		msg.push_back(tmp[i]);

	c->write(0x0204, msg);
}


void Lobby::askforLobbyData()
{
		vector<unsigned char> leer;

		c->write(0x0201,leer);
}

void Lobby::processNewMessage(short id,vector<unsigned char> data)
{
	switch (id)
	{
		//	00: 	Server -> Client (sendet Lobby-Daten)
		//	01: 	Client -> Server (fordert Lobby-Daten an)
	case 0x0200:
		{
			m.lock();

			unsigned int i = 0;
			while (i < data.size())
			{
				short id = decodeShort(data, i);
				i+=2;
				short playerlimit = decodeShort(data, i);
				i+=2;
				short len = decodeShort(data, i);
				i+=2;
				string gamename = decodeString(data, i, len);
				i+=len;
				len = decodeShort(data, i);
				i+=2;
				string mastername = decodeString(data, i, len);
				PlayerData master;
				master.Name = mastername;
				i+=len;
				short countplayers = decodeShort(data,i);
				i+=2;
				std::vector<PlayerData> players;
				for (int j = 0; j < countplayers; j++)
				{
					len = decodeShort(data, i);
					i+=2;
					string playername = decodeString(data, i, len);
					i+=len;
					PlayerData player;
					player.Name = playername;
					players.push_back(player);
				}
				GameData game;
				game.playerlimit = playerlimit;
				game.gameMaster = master;
				game.players = players;
				game.name = gamename;
				gamesCreated[id] = game;
			}

			updated = true;
			m.unlock();

			break;
		}
		//	02:		Client -> Server (will zu Spiellobby connecten)
		//	03: 	Server -> Client (connect Bestätigung)
	case 0x0203:
		{
			if (data[0] == 1)
			{
				inGameLobby = true;
				updated = true;//connect erfolgreich, tu was
				//gamelobbypointer auf das ausgewählte game setzen, den Spieler dort hinzufügen
			}
			else;
				//connect nicht erfolgreich, tu was
				//zu viele spieler oder so, anzeigen!
			break;
		}
		//	04:		Client -> Server (will Spiellobby erstellen)
		//	05: 	Server -> Client (erstellen Bestätigung)
	case 0x0205:
		{
			if (data[0] == 1)
			{
				inGameLobby = true;
				updated = true;//this->gameLobby = new GameLobby();
			}
			else;
				//erstellen nicht erfolgreich, tu was
			break;
		}
	}
}

void Lobby::processNetworkError(int id, std::string msg)
{
}