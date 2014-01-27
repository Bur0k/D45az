#include <vld.h>

#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
	for(std::vector<MapLayer*>::iterator it=layers.begin();it!=layers.end();it++)
		delete *it;
	layers.clear();
}

void Map::load(std::string MapLocation)
{
	for(std::vector<MapLayer*>::iterator it=layers.begin();it!=layers.end();it++)
		delete *it;
	layers.clear();

	TiXmlDocument LevelMap(MapLocation.c_str());
	LevelMap.LoadFile();

	TiXmlElement* root = LevelMap.FirstChildElement();
	if ( root )
	{
		for(TiXmlElement* element = root->FirstChildElement("tileset");element;element=element->NextSiblingElement("tileset"))
		{
			std::string Location=element->FirstChildElement()->Attribute("source");
			Location="Data/Maps/"+Location;
		}
		for(TiXmlElement* element = root->FirstChildElement("layer");element;element=element->NextSiblingElement("layer"))
		{
			std::string LayerName(element->Attribute("name"));
			bool isCityLayer=false,isBarricadeLayer=false,isCityTerrainLayer=false;
			if(std::string::npos != LayerName.find("CityLayer"))
				isCityLayer=true;
			else if(std::string::npos != LayerName.find("BarricadeLayer"))
				isBarricadeLayer=true;
			else if(std::string::npos != LayerName.find("CityTerrain"))
				isCityTerrainLayer=true;

			const char* temptt = element->FirstChildElement()->GetText();
			int tempii = std::atoi(root->Attribute("width"));

			layers.push_back(new MapLayer(temptt,tempii,isCityLayer,isBarricadeLayer,isCityTerrainLayer));
		}
	}
}