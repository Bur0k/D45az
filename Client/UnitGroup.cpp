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

	float strategyfactor;
	if (this->strategy == UnitStrategy::DEFENSIVE)
		strategyfactor = (float)def;
	if (this->strategy == UnitStrategy::OFFENSIVE)
		strategyfactor = (float)off;
	if (this->strategy == UnitStrategy::RUNNING)
		strategyfactor = (float)run;

	for (int i = 0; i < 16; i++)
	{
		strength += this->units[i].count * strategyfactor;
		switch (this->units[i].type)
		{
		case UnitTypes::LIGHT:
			strength += (float)(this->units[i].count * light);
			break;
		case UnitTypes::HEAVY:
			strength += (float)(this->units[i].count * heavy);
			break;
		case UnitTypes::LONGRANGE:
			strength += (float)(this->units[i].count * longrange);
			break;
		case UnitTypes::ARTILLERY:
			strength += (float)(this->units[i].count * artillery);
			break;
		default:
			break;
		}
	}

	strength = strength / maxstrength;

	return strength;
}