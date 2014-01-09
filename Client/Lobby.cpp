//	0x02:	Lobby-Logik
//	00: 	Server -> Client (sendet Lobby-Daten)
//	01: 	Client -> Server (fordert Lobby-Daten an)
//	02:		Client -> Server (will zu Spiellobby connecten)
//	03: 	Server -> Client (connect Bestätigung)
//	04:		Client -> Server (will Spiellobby erstellen)
//	05: 	Server -> Client (erstellen Bestätigung)


#include "Lobby.h"

void Lobby::processNewMessage(short id,vector<char> data)
{
	switch (id)
	{
		//	00: 	Server -> Client (sendet Lobby-Daten)
		//	01: 	Client -> Server (fordert Lobby-Daten an)
	case 0x0201:
		{
			break;
		}
		//	02:		Client -> Server (will zu Spiellobby connecten)
		//	03: 	Server -> Client (connect Bestätigung)
	case 0x0203:
		{
			break;
		}
		//	04:		Client -> Server (will Spiellobby erstellen)
		//	05: 	Server -> Client (erstellen Bestätigung)
	case 0x0205:
		{
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