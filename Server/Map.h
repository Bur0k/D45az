#ifndef MAP_H
#define MAP_H

#include "MapLayer.h"
#include <vector>
#include <string>
#include "TileSets.h"
#include "tinyxml.h"

class Map
{
	TileSets* tilesets;
	sf::Vector2i size;

public:
	Map();
	~Map();
	
	std::vector<MapLayer*> layers;
	void load(std::string MapLocation);
	sf::Vector2i getLayerCount();//Gives the number of Rows and Colums of the first Layer
};
#endif