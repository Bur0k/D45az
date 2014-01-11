#ifndef GRAPHIC_GLOBALS_H
#define GRAPHIC_GLOBALS_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;

class _MyColors
{
public:
	Color Black;
	Color Orange;
	Color Azure;
	Color Gray;
	Color White;
	Color Red;

	_MyColors() {
		Orange = Color(0xFF, 0xA2, 0x00, 0xFF);
		Azure = Color(0x00, 0xFF, 0x6A, 0xFF);
		Gray = Color(0x80, 0x80, 0x80, 0xFF);
		Black = Color::Black;
		White = Color::White;
		Red = Color::Red;
	}
} static MyColors;

enum GameFonts {ARIAL};


class MyFonts
{
private:
		MyFonts();
public:
	static sf::Font* s_pArial;
	
	static void deleteFonts();
	static sf::Font & getFont(GameFonts);
	
}; 


struct SpriteTex
{
	Texture t;
	RectangleShape s;
};

typedef std::vector<SpriteTex>SpriteTexVect;
#endif