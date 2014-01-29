#include "UnitGroup.h"

// umschreiben
UnitGroup::UnitGroup(POINT pos, UnitTypes types[16], short livingsoldiers[16])
{
	this->units = new soldiers[16];
	this->pos = pos;

	for (int i = 0; i < 16; i++)
	{
		this->units[i].count = livingsoldiers[i];
		if (livingsoldiers[i] != 0)
			this->units[i].type = types[i];
	}

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