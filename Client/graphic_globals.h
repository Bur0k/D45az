#ifndef GRAPHIC_GLOBALS_H
#define GRAPHIC_GLOBALS_H

#include <SFML\Graphics.hpp>
#include <iostream>
using namespace sf;

class _MyColors
{
public:
	Color Black;
	Color Orange;
	Color Azure;
	Color Gray;
	Color White;

	_MyColors() {
		Orange = Color(0xFF, 0xA2, 0x00, 0xFF);
		Azure = Color(0x00, 0xFF, 0x6A, 0xFF);
		Gray = Color(0x80, 0x80, 0x80, 0xFF);
		Black = Color::Black;
		White = Color::White;
	}
} static MyColors;


class _MyFonts
{
public:
	sf::Font Arial;

	_MyFonts() {
		if(!Arial.loadFromFile("Data/Fonts/arial.ttf"))
			std::cout << "font arial load failed!!" << std::endl;
	}
} static MyFonts;

#endif