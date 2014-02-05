#ifndef STANDARDBUTTON_H
#define STANDARDBUTTON_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "Button.h"
#include "SplittedSprite.h"
#include "graphic_globals.h"


using namespace sf;



//adjust it to your sprite file
#define BUTTONTILESIZE 10

//go-to-button if you don't need any special features
class StandardButton : public Button
{
private:
	sf::RectangleShape m_Rect;
	SpriteTex* m_pST;
	
	int m_buttonTileSize;
	/* Sprite Layout
		0 1 2
		3 - 4
		5 6 7
	*/



	//if position of parent rectangle changes adjust current graphics
	void updatePosition();

public:


	StandardButton();
	///@param Size x or y should be bigger than 10 px
	StandardButton(Vector2f pos, Vector2f size, sf::String S, int ID, bool lock, bool big = true);
	~StandardButton();

	void draw(RenderWindow* rw);
	//gets called by parent class
	void updateVisuals();
};


#endif