#include <vld.h>
#include "MapLayer.h"

MapLayer::MapLayer(std::string LI,int RowNum,TileSets* TileSets,bool IsCollisionLayer)
{
	isCollisionLayer=IsCollisionLayer;
	tilesets=TileSets;
	
	std::stringstream stream(LI);
	std::string temp;
	std::vector<short> tempEntry;

	for(int i=0;std::getline(stream,temp,',');i++)
	{
		if(i==RowNum)
		{
			i=0;
			layer.push_back(tempEntry);
			tempEntry=std::vector<short>();
		}
		tempEntry.push_back(std::atoi(temp.c_str()));
	}
	layer.push_back(tempEntry);
}

MapLayer::~MapLayer()
{

}

void MapLayer::render(sf::RenderTarget& RT,sf::IntRect OnScreen)
{
	/*int firstX=OnScreen.left/TileWidth;
	int firstY=OnScreen.top/TileHeight;*/

	int width=OnScreen.width / TileWidth + 
		((OnScreen.top+OnScreen.width % TileWidth  > 0)? 1 : 0);

	int heigth=OnScreen.height / TileHeight + 
		((OnScreen.left+OnScreen.height  % TileHeight > 0)? 1 : 0) ;

	int firstY=OnScreen.top/TileHeight;
	int firstX=OnScreen.left/TileWidth;

	for(int y=firstY ; y!=firstY+heigth ; y++)
		for(int x=firstX ; x!=firstX+width ; x++)
		{
			SplittedSprite* temp=tilesets->get(layer[y][x]);
			if(temp)
			{
				temp->setPosition((float)x*TileWidth,(float)y*TileHeight);
				RT.draw(*temp);
			}
		}
}

sf::Vector2i MapLayer::getLayerCount()
{
	return sf::Vector2i(((layer.size()>0)?layer[0].size():0),layer.size());
}