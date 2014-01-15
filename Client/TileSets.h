#ifndef _TILESETS_
#define _TILESETS_

#include <SFML\Graphics.hpp>
#include "SplittedSprite.h"
#include <string>
#include <vector>
#include <map>

class TileSets
{
	std::vector<int> firstgid;
	std::vector<sf::Texture*> texture;
	std::vector<sf::Image*> images;
	std::vector<SplittedSprite*> sprite;

public:
	TileSets();
	~TileSets();

	void addTileSet(std::string Location,int FirstGID,int width,int height);
	SplittedSprite* get(int GID);
	sf::Image* getImage(int GID);
};

#endif