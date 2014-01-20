#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "SplittedSprite.h"
#include <iostream>
#include "TileSets.h"

class MapLayer
{
	TileSets* tilesets;
public:
	std::vector<std::vector<short>> layer;
	bool isCityLayer;
	const static int TileWidth=32;
	const static int TileHeight=32;

	MapLayer(std::string LayerInformation,int RowNum,TileSets* TileSets,bool IsCityLayer=false);
	~MapLayer();

	void render(sf::RenderTarget& RT,sf::IntRect OnScreen);
	sf::Vector2i getLayerCount();
};