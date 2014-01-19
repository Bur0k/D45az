#ifndef MAP_H
#define MAP_H

#include "MapLayer.h"
#include <vector>
#include <string>
#include "tinyxml.h"

class Map
{
public:
	Map();
	~Map();
	
	std::vector<MapLayer*> layers;
	void load(std::string MapLocation);
};
#endif