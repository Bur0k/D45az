#include <vld.h>

#include "TileSets.h"

TileSets::TileSets()
{
}

TileSets::~TileSets()
{
	for(std::vector<SplittedSprite*>::iterator it=sprite.begin();it!=sprite.end();it++)
		delete *it;
	for(std::vector<sf::Texture*>::iterator it=texture.begin();it!=texture.end();it++)
		delete *it;
	for(std::vector<sf::Image*>::iterator it=images.begin();it!=images.end();it++)
		delete *it;
}

void TileSets::addTileSet(std::string Location,int FirstGID,int width,int height)
{
	firstgid.push_back(FirstGID);
	sf::Texture* tex=new sf::Texture();
	tex->loadFromFile(Location);
	texture.push_back(tex);
	SplittedSprite* temp=new SplittedSprite(tex,width,height);
	sprite.push_back(temp);
	images.push_back(new sf::Image(tex->copyToImage()));
}

SplittedSprite* TileSets::get(int GID)
{
	if(GID==0)
		return NULL;


	GID-=1;

	int i=0;
	int index=0;
	for(std::vector<int>::iterator it=firstgid.begin();it!=firstgid.end();it++)
	{
		if(GID>=*it)
			index=i;
		i++;
	}

	SplittedSprite* temp = sprite.at(index);
	temp->setFrame(GID-firstgid.at(index)+1);
	return temp;
}

sf::Image* TileSets::getImage(int GID)
{
	if(GID==0)
		return NULL;


	GID-=1;

	int i=0;
	int index=0;
	for(std::vector<int>::iterator it=firstgid.begin();it!=firstgid.end();it++)
	{
		if(GID>=*it)
			index=i;
		i++;
	}
	return images[i];
}