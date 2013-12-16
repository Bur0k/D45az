#include "LogInLogic.h"

LogInLogic::LogInLogic()
{

}

void LogInLogic::connect()
{
	bool userexists = false;
	short id;
	vector<char> data;

	if (id == 0x0100)
	{
		string name = "";

		//testen
		for (int i = 0; i < data.size(); i++) 
			name += data[i];

		for (int i = 0; i < connectedUsers.size(); i++)
		{
			if (connectedUsers[i]->getName()  == name)
			{// send 0101 nachricht 0
				userexists = true;
				break;
			}
		}
		if (!userexists)
		{
			User* u = new User(name);
			connectedUsers.push_back(u);

			//send 0101 nachricht 1
		}

	}
}

