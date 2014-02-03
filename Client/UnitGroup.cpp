#include "UnitGroup.h"

// umschreiben
UnitGroup::UnitGroup(POINT pos, UnitTypes types[16], short livingsoldiers[16], UnitStrategy strategy, City* producer)
{
	this->strategy = strategy;
	this->units = new soldiers[16];
	this->pos = pos;

	for (int i = 0; i < 16; i++)
	{
		this->units[i].count = livingsoldiers[i];
		if (livingsoldiers[i] != 0)
			this->units[i].type = types[i];
	}

	this->player_ID = producer->player_ID;
}

UnitGroup::~UnitGroup()
{
	delete[] units;
}

void UnitGroup::processNewMessage(short id,vector<char> data)
{

}

void UnitGroup::processNetworkError(int id, std::string msg)
{

}

float UnitGroup::getUnitgroupStrength()
{
	
	return 1.0;
}