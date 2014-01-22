#ifndef CITY_H
#define CITY_H

#include "NetworkParticipant.h"
#include "Client.h"
#include <SFML\Graphics.hpp>

class City : public NetworkParticipant
{

	sf::Vector2i position;
	int level;

public:
	City(sf::Vector2i position, int level);
	~City();
};

#endif