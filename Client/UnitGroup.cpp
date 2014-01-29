#include "UnitGroup.h"

UnitGroup::UnitGroup(POINT pos, short countLight, short countHeavy, short countLongrange, short countArtillery)
{
	this->units = new soldiers[4];
	this->pos = pos;

	this->units[0].count = countLight;
	this->units[0].type = UnitTypes::LIGHT;
	this->units[1].count = countHeavy;
	this->units[1].type = UnitTypes::HEAVY;
	this->units[2].count = countLongrange;
	this->units[2].type = UnitTypes::LONGRANGE;
	this->units[3].count = countArtillery;
	this->units[3].type = UnitTypes::ARTILLERY;
	this->units[4].count = countArtillery;
	this->units[4].type = UnitTypes::ARTILLERY;

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