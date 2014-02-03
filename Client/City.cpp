#include "City.h"

City::City(sf::Vector2i position, int level, short id)
{
	this->position = position;
	this->level = level;
	this->generatedIncome = 0;
	this->player_ID = id;
}

City::~City()
{
}
