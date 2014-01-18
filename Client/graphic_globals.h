#ifndef GRAPHIC_GLOBALS_H
#define GRAPHIC_GLOBALS_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;



class MyColors
{
public:
	Color Black;
	Color Orange;
	Color Azure;
	Color Gray;
	Color DarkGray;
	Color White;
	Color Red;
	Color Transparent;

	MyColors() {
		Orange = Color(0xFF, 0xA2, 0x00, 0xFF);
		Azure = Color(0x00, 0xFF, 0x6A, 0xFF);
		Gray = Color(0x80, 0x80, 0x80, 0xFF);
		DarkGray = Color(0x40, 0x40, 0x40, 0xFF);
		Black = Color::Black;
		White = Color::White;
		Red = Color::Red;
		Transparent = Color::Transparent;
	}
} static MyColors;



enum class GameFonts {ARIAL};

//singleton style with Lazy initialization
//font accessible via getFont(GameFonts); 
class MyFonts
{
private:
	MyFonts();
public:
	static sf::Font* s_pArial;
	
	static void deleteFonts();
	static sf::Font & getFont(GameFonts);
};



//since you need the texture for your rectangle alive get those two in one struct
struct SpriteTex
{
	Texture t;
	RectangleShape s;
};

typedef std::vector<SpriteTex>SpriteTexVect;
#endif