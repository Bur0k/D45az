#pragma once

#include <vector>
#include "TileSets.h"
#include <string>
#include <sstream>
#include "SplittedSprite.h"
#include <SFML\Graphics.hpp>
#include <iostream>

class MapLayer
{
	std::vector<std::vector<short>> layer;
	TileSets* tilesets;

public:
	bool isCollisionLayer;
	const static int TileWidth=64;
	const static int TileHeight=64;

	MapLayer(std::string LayerInformation,int RowNum,TileSets* TileSets,bool IsCollisionLayer=false);
	~MapLayer();

	void render(sf::RenderTarget& RT,sf::IntRect OnScreen);
	sf::Vector2i getLayerCount();
};