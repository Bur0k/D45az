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
	Color MenuBackground;
	Color WhiteTransparent;
	Color BlueTransparent;
	Color Chartreuse;
	Color Gold;
	Color Silver;
	Color Bronze;
	Color player[4];
	Color ButtonColor;
	

	MyColors() {
		Orange = Color(0xFF, 0xA2, 0x00, 0xFF);
		Azure = Color(0x00, 0xFF, 0x6A, 0xFF);
		Gray = Color(0x80, 0x80, 0x80, 0xFF);
		DarkGray = Color(0x40, 0x40, 0x40, 0xFF);
		MenuBackground = Color(0,0,0, 0xA0);
		Chartreuse = Color(0x7f, 0xff, 0x0, 0xFA); 
		WhiteTransparent = Color(0xFF, 0xFF, 0xFF, 0x80);
		BlueTransparent = Color(0x0, 0x0, 0xFF, 0x80);
		Gold = Color(201,137,16);
		Silver = Color(168,168,168);
		Bronze = Color(150,90,56);
		ButtonColor = Color(0xE0,0xE0,0xE0,0xFF);

		Black = Color::Black;
		White = Color::White;
		Red = Color::Red;

		player[0] = Red;
		player[1] = Color::Blue;
		player[2] = Color(0x0C,0xED,0x00,0xFF);	//green
		player[3] = Color(0xFF,0xFB,0x00,0xFF);	//yellow
		player[5] = Color::White;	//neutral color

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




//types of objects that can be on a game map
enum class ingameObjectType{
	ARMY,
	CITY
};

//interface for all objects that are displayed on the game map
class IIngameObjects
{
	virtual ingameObjectType getType()=0;
	virtual void onMapMove(Rect<int>)=0;
};








#endif