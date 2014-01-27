#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML\Graphics.hpp>
#include "IDrawable.h"
#include "graphic_globals.h"

class Background
	: public IDrawable 
{
private:
	SpriteTex bgimage;
public:
	Background();
	Background(std::string path);
	~Background();
	//IDrawable
	void draw(sf::RenderWindow* rw);
	void onResize(sf::Vector2u &);
};



#endif //BACKGROUND_H