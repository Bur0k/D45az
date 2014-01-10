#include <vld.h>

#include "Map.h"

Map::Map()
{
	tilesets=NULL;
}

Map::~Map()
{
	if(tilesets!=NULL)
		delete tilesets;
	for(std::vector<MapLayer*>::iterator it=layers.begin();it!=layers.end();it++)
		delete *it;
	layers.clear();
}

void Map::load(std::string MapLocation)
{
	if(tilesets!=NULL)
	{
		delete tilesets;

		for(std::vector<MapLayer*>::iterator it=layers.begin();it!=layers.end();it++)
			delete *it;
		layers.clear();
	}

	TiXmlDocument LevelMap(MapLocation.c_str());
	LevelMap.LoadFile();

	TiXmlElement* root = LevelMap.FirstChildElement();
	if ( root )
	{
		tilesets = new TileSets();
		size.x=std::atoi(root->Attribute("width"))*std::atoi(root->Attribute("tilewidth"));
		size.y=std::atoi(root->Attribute("height"))*std::atoi(root->Attribute("tileheight"));

		for(TiXmlElement* element = root->FirstChildElement("tileset");element;element=element->NextSiblingElement("tileset"))
		{
			std::string Location=element->FirstChildElement()->Attribute("source");
			Location="Data/Maps/"+Location;

			tilesets->addTileSet(Location,std::atoi(element->Attribute("firstgid")),std::atoi(element->Attribute("tilewidth")),std::atoi(element->Attribute("tileheight")));
		}
		for(TiXmlElement* element = root->FirstChildElement("layer");element;element=element->NextSiblingElement("layer"))
		{
			std::string isCollisionLayer(element->Attribute("name"));
			bool isCollision=false;
			if(std::string::npos != isCollisionLayer.find("Collision"))
				isCollision=true;

			const char* temptt = element->FirstChildElement()->GetText();
			int tempii = std::atoi(root->Attribute("width"));

			layers.push_back(new MapLayer(temptt,tempii,tilesets,isCollision));
		}
	}
}

void Map::render(sf::RenderTarget& RT,sf::IntRect View)
{
	for(std::vector<MapLayer*>::iterator it=layers.begin();it!=layers.end();it++)
		(*it)->render(RT,View);
}

sf::Vector2i Map::getLayerCount()
{
	return layers[0]->getLayerCount();
}