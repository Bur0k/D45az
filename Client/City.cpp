#include "City.h"

City::City(sf::Vector2i position, int level)
{
	this->position = position;
	this->level = level;
	this->generatedIncome = 0;
}

City::~City()
{
}
