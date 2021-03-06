#include "IngameLogic.h"

IngameLogic::IngameLogic(int id, PlayerData owner, CityLogic* startCity)
{
	this->server = Server::get();

	this->cities.push_back(startCity);
	this->player_ID = id;

	server->addToNewMessageCallback(this);
	server->addToErrorCallback(this); // as

	this->owner = owner;
	this->gold = 500;

	POINT p;
	p.x = startCity->position->x;
	p.y = startCity->position->y + 2;

	UnitTypes type = UnitTypes::LIGHT;

	UnitGroupLogic* uGroup = new UnitGroupLogic(8, type, p, &this->unitGroups);
	uGroup->player_ID = startCity->player_ID;
}

IngameLogic::~IngameLogic()
{
	server->deleteFromNewMessageCallback(this);
	server->deleteFromErrorCallback(this);
}


void IngameLogic::processNewMessage(SOCKET s,short id,std::vector<unsigned char> data)
{
	vector<unsigned char> erfg;

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
			// muss noch richtig initialisiert/ ausgelesen werden
			UnitTypes type = UnitTypes::ARTILLERY;

			//TODO
			// Poition muss noch mit �bergeben werden!
			POINT pos;
			pos.x = 1;
			pos.y = 1;
			

			UnitGroupLogic* uGroup = new UnitGroupLogic(units, type, pos, &this->unitGroups);
			//this->unitGroups.push_back(uGroup); wird im konstruktor erledigt
			this->server->write(s, 0x0505, erfg); 
		}
	}
}
	
void IngameLogic::processNetworkError(SOCKET s,int errCode,std::string errMessage)
{

}