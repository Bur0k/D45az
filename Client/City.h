#ifndef CITY_H
#define CITY_H

#include "Client.h"
#include <SFML\Graphics.hpp>

class City
{
public:
	sf::Vector2i position;
	int level;
	int generatedIncome;
	short player_ID;


	City(sf::Vector2i position, int level, short id);
	~City();
};

#endif