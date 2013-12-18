#include "LogInLogic.h"

LogInLogic::LogInLogic()
{
	//Message Callback Anmelden nicht vergessen!
}

LogInLogic::~LogInLogic()
{
	for(int i = 0; i < connectedUsers.size(); i++)
		delete connectedUsers[i];
}

void LogInLogic::LogicMessageCallback(ClientHandler* ch,short id,vector<char> data)
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

			for (int i = 0; i < connectedUsers.size(); i++)
			{
				if (connectedUsers[i]->getName()  == name)
				{
					// send 0101 nachricht 0
					std::vector<char> erfg;
					erfg.push_back(0);
					ch->write(0x0101,erfg);

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
					ch->write(0x0101,erfg);
			}
		}break;
	}
}