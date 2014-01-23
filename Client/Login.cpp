#include "Login.h"

void Login::processNewMessage(short id,vector<char> data)
{
	if(id==0x0101)
	{
		if(data[0])
		{
			state = 1;
		}
		else
		{ 
			state = -1;
		}
	}
}

void Login::processNetworkError(int id, std::string msg)
{
}

Login::Login(string Name)
{
	state = 0;
	c = Client::get();
	c->addToNewMessageCallback(this);

	if(Name.size() < 10)
	{
		vector<char> charName;
		for(unsigned int i=0;i<Name.size();i++)
			charName.push_back(Name.at(i));

		c->write(0x0100,charName);
	}
}

Login::~Login()
{
	c->deleteFromNewMessageCallback(this);
}

//returns 0 for no Response until now, returns 1 for name can be used returns -1 for name is already used
short Login::getState()
{
	return state;
}