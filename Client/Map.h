#pragma once

//#include "MapLayer.h"
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
//#include "TileSets.h"
#include "tinyxml.h"
//#include "BaseGameEntity.h"
//#include "Base_Shot.h"
//#include "CollisionMask.h"

class Map
{
	std::vector<MapLayer*> layers;
	TileSets* tilesets;
	sf::Vector2i size;

public:
	Map();
	~Map();

	void load(std::string MapLocation);
	void render(sf::RenderTarget& RT,sf::IntRect View);
	sf::Vector2i getLayerCount();//Gives the number of Rows and Colums of the first Layer
};