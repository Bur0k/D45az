#include "LogInLogic.h"

LogInLogic::LogInLogic()
{
	self = this;
	this->server = Server::get();

	server->newMessageCallback.push_back(LogicMessageCallback);
}

LogInLogic::~LogInLogic()
{
	for(int i = 0; i < connectedUsers.size(); i++)
		delete connectedUsers[i];
}

void LogInLogic::LogicMessageCallback(SOCKET s,short id,vector<char> data)
{
	switch(id)
	{
	case 0x0100:
		{
			bool userexists = false;
			string name = "";

			//testen
			for (int i = 0; i < data.size(); i++) 
				name += data[i];

			for (int i = 0; i < LogInLogic::self->connectedUsers.size(); i++)
			{
				if (LogInLogic::self->connectedUsers[i]->getName()  == name)
				{
					// send 0101 nachricht 0
					std::vector<char> erfg;
					erfg.push_back(0);
					LogInLogic::self->server->write(s,0x0101,erfg);

					userexists = true;
					break;
				}
			}

			if (!userexists)
			{
				User* u = new User(name);
				LogInLogic::self->connectedUsers.push_back(u);

				//send 0101 nachricht 1
				std::vector<char> erfg;
				erfg.push_back(1);
				LogInLogic::self->server->write(s,0x0101,erfg);

			}
		}break;
	}
}