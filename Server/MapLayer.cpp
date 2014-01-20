#include <vld.h>
#include "MapLayer.h"

MapLayer::MapLayer(std::string LI,int RowNum,bool IsCityLayer)
{
	isCityLayer=IsCityLayer;
	
	std::stringstream stream(LI);
	std::string temp;
	std::vector<short> tempEntry;

	//TileSets->

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