#include "IngameLogic.h"

IngameLogic::IngameLogic(PlayerData* owner)
{
	this->server = Server::get();

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this);

	this->owner = owner;
}

IngameLogic::~IngameLogic()
{
	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
}


void IngameLogic::processNewMessage(SOCKET s,short id,std::vector<char> data)
{
	vector<char> erfg;

	switch(id)
	{
	case 0x0500:
		{

		}
	case 0x0502:
		{

		}
	case 0x0504:
		{
			short units = data[0];
			short type = data[1];

			//TODO
			// Poition muss noch mit übergeben werden!

			UnitGroupLogic* uGroup = new UnitGroupLogic(units, type);
			this->unitGroups.push_back(uGroup);
			this->server->write(s, 0x0505, erfg); 
		}
	}
}
	
void IngameLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{

}