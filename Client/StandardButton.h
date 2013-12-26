#ifndef STANDARDBUTTON_H
#define STANDARDBUTTON_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "Button.h"
#include "SplittedSprite.h"

using namespace sf;

struct SpriteTex
{
	Texture t;
	RectangleShape s;
};

//adjust it to your sprite file
const int BUTTONTILESIZE = 10;

//go-to-button if you don't need any special features
class StandardButton : public Button
{
private:
	sf::RectangleShape m_Rect;
	SpriteTex* m_pST;
	
	/* Sprite Layout
		0 1 2
		3 - 4
		5 6 7
	*/

	//gets called by parent class
	void updateVisuals(bool colorCange);

public:
	StandardButton();
	///@param Size x or y should be bigger than 10 px
	StandardButton(Vector2f pos, Vector2f size, sf::String S, int ID);
	~StandardButton();

	void draw(RenderWindow* rw);
};


#endif