#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class MapLayer
{
public:
	std::vector<std::vector<short>> layer;
	bool isCityLayer;
	bool isMountainLayer;
	const static int TileWidth=32;
	const static int TileHeight=32;

	MapLayer(std::string LayerInformation,int RowNum,bool IsCityLayer=false);
	~MapLayer();

};