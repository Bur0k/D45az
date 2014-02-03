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
	float strength = 0;
	// bis zu 0.9 für maximale Anzahl an Einheiten in der group, die restlichen 0.1 entstehen durch die mischung der einheiten 
	short countlight = 0;
	short countheavy = 0;
	short countlongrange = 0;
	short countartillery = 0;

	for (int i = 0; i < 16; i++)
	{
		strength += (float)((0.9/16.0) * (this->units->count / maxlivingsoldiers));
		switch (this->units->type)
		{
		case UnitTypes::LIGHT:
			countlight++;
			break;
		case UnitTypes::HEAVY:
			countheavy++;
			break;
		case UnitTypes::LONGRANGE:
			countlongrange++;
			break;
		case UnitTypes::ARTILLERY:
			countartillery++;
			break;
		default:
			break;
		}
	}

	if (countlight != 0)
		strength += (float)0.1/4.0;
	if (countheavy != 0)
		strength += (float)0.1/4.0;
	if (countlongrange != 0)
		strength += (float)0.1/4.0;
	if (countartillery != 0)
		strength += (float)0.1/4.0;

	return strength;
}