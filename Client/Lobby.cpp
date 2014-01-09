//	0x02:	Lobby-Logik
//	00: 	Server -> Client (sendet Lobby-Daten)
//	01: 	Client -> Server (fordert Lobby-Daten an)
//	02:		Client -> Server (will zu Spiellobby connecten)
//	03: 	Server -> Client (connect Bestätigung)
//	04:		Client -> Server (will Spiellobby erstellen)
//	05: 	Server -> Client (erstellen Bestätigung)


#include "Lobby.h"

void Lobby::connectToGameLobby(char mapid)
{
	vector<char> msg;
	msg.push_back(mapid);

	c->write(0x0202, msg);
}
void Lobby::createNewGameLobby()
{
	vector<char> leer;

	c->write(0x0204, leer);
}


void Lobby::askforLobbyData()
{
		vector<char> leer;

		c->write(0x0201,leer);
}

void Lobby::processNewMessage(short id,vector<char> data)
{
	switch (id)
	{
		//	00: 	Server -> Client (sendet Lobby-Daten)
		//	01: 	Client -> Server (fordert Lobby-Daten an)
	case 0x0200:
		{
			unsigned int i = 0;
			while (i < data.size())
			{
				char mapid = data[i];
				i+=1;
				short gameid = decodeShort(data, i);
				i+=2;
				short playerlimit = decodeShort(data, i);
				i+=2;
				short len = decodeShort(data, i);
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
				game.id = gameid;
				game.playerlimit = playerlimit;
				game.gameMaster = &master;
				game.players = players;
				gamesCreated[mapid] = game;
			}

			break;
		}
		//	02:		Client -> Server (will zu Spiellobby connecten)
		//	03: 	Server -> Client (connect Bestätigung)
	case 0x0203:
		{
			if (data[0] == 1);
				//connect erfolgreich, tu was
			else;
				//connect nicht erfolgreich, tu was
			break;
		}
		//	04:		Client -> Server (will Spiellobby erstellen)
		//	05: 	Server -> Client (erstellen Bestätigung)
	case 0x0205:
		{
			if (data[0] == 1);
				//erstelle erfolgreich, tu was
			else;
				//erstellen nicht erfolgreich, tu was
			break;
		}
	}
}

void Lobby::processNetworkError(int id, std::string msg)
{
}

Lobby::Lobby(string Name)
{
	c = Client::get();
	c->addToNewMessageCallback(this);

	this->name = Name;
}

Lobby::~Lobby()
{
	c->deleteFromNewMessageCallback(this);
}