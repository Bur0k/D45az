#include "NetworkLogin.h"

void NetworkLogin::processNewMessage(short id,vector<char> data)
{
	if(id==0x0101)
	{
		if(data[0])
		{
			state = 1;
		}
		else
		{
			state = 0;
		}
	}
}

void NetworkLogin::processNetworkError(int id, std::string msg)
{
}

NetworkLogin::NetworkLogin(string Name)
{
	state = 0;
	c = Client::get();
	c->addToNewMessageCallback(this);

	vector<char> charName;
	for(int i=0;i<Name.size();i++)
		charName.push_back(Name.at(i));

	c->write(0x0100,charName);
}

NetworkLogin::~NetworkLogin()
{
	c->deleteFromNewMessageCallback(this);
}

//returns 0 for no Response until now, returns 1 for name can be used returns -1 for name is already used
short NetworkLogin::getState()
{
	return state;
}