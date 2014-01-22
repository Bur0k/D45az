#include "Connect.h"

void Connect::processNewMessage(short id,vector<char> data)
{
	if(id==0x0001)
	{
		c->beginRead();
		c->write(0,std::vector<char>());//Einmal irgendwas senden. Muss sein
		state = 1;
	}
}

void Connect::processNetworkError(int id, std::string msg)
{
	if(id < 0 && id > -6)
	{
		state = -1;
		errorMsg = new std::string(msg);
	}
}

Connect::Connect()
{
	state = 0;
	errorMsg=nullptr;
	
	c = Client::get();
	c->addToErrorCallback(this);
	c->addToNewMessageCallback(this);
	c->connectToServer("localhost",4242);

}

Connect::~Connect()
{
	c->deleteFromNewMessageCallback(this);
	c->deleteFromErrorCallback(this);

	if(errorMsg.operator std::string *() != nullptr)
		delete errorMsg.operator std::string *();
}

//returns 0 for no Response until now, returns 1 for name can be used returns -1 for name is already used
short Connect::getState()
{
	return state;
}