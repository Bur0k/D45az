#include "LogInLogic.h"

LogInLogic::LogInLogic()
{
	this->server = Server::get();
	server->addToNewMessageCallback(this);
}

LogInLogic::~LogInLogic()
{
	for(unsigned int i = 0; i < connectedUsers.size(); i++)
		delete connectedUsers[i];
	server->deleteFromNewMessageCallback(this);
}

vector<User*>& LogInLogic::getconnectedUsers()
{
	return this->connectedUsers;
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

			for (unsigned int i = 0; i < connectedUsers.size(); i++)
			{
				if (connectedUsers[i]->getName()  == name)
				{
					// send 0101 nachricht 0
					std::vector<char> erfg;
					erfg.push_back(0);
					server->write(s,0x0101,erfg);

					userexists = true;
					break;
				}
			}

			if (!userexists)
			{
				User* u = new User(name);
				connectedUsers.push_back(u);

				//send 0101 nachricht 1
				std::vector<char> erfg;
				erfg.push_back(1);
				server->write(s,0x0101,erfg);
			}
		}break;
	}
}

void LogInLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{
}