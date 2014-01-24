#include "LogInLogic.h"

LogInLogic::LogInLogic()
{
	this->server = Server::get();
	server->addToNewMessageCallback(this);
}

LogInLogic::~LogInLogic()
{
	//for(unsigned int i = 0; i < connectedUsers.size(); i++)
	//	delete connectedUsers[i];
	server->deleteFromNewMessageCallback(this);
}

void LogInLogic::processNewMessage(SOCKET s,short id,vector<char> data)
{
	switch(id)
	{
	case 0x0100:
		{
			bool userexists = false;
			string name = "";

			//testen
			for (unsigned int i = 0; i < data.size(); i++) 
				name += data[i];


			if(name.size() > 3 && name.size() <= 10)
			{
				for (unsigned int i = 0; i < server->connectedPlayers.size(); i++)
				{
					if (server->connectedPlayers[i].Name == name)
					{
						std::vector<char> erfg;
						erfg.push_back(0);
						server->write(s,0x0101,erfg);

						userexists = true;
						break;
					}
				}

				if (!userexists)
				{
					PlayerData newPlayer;
					newPlayer.Name=name;
					newPlayer.s=s;
					server->connectedPlayers.push_back(newPlayer);

					//send 0101 nachricht 1
					std::vector<char> erfg;
					erfg.push_back(1);
					server->write(s,0x0101,erfg);
				}
			}
			else
			{
				std::vector<char> erfg;
				erfg.push_back((char)-1);
				server->write(s,0x0101,erfg);
			}
		}break;
	}
}

void LogInLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
}