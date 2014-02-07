#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <string> 

#include "IClickable.h"
#include "graphic_globals.h"
#include "IDrawable.h"
#include "IAnimatable.h"

#include "StandardButton.h"
#include "Textblock.h"

//#define Statusbarheight 50.0
//#define IconOffset 150.0
//#define LabelOffset 200.0
//#define IconX 170.0
//#define IconY 5.0

static const float Statusbarheight = 50.0;
static const float IconOffset = 150.0;
static const float LabelOffset = 200.0;
static const float IconX = 170.0;
static const float IconY = 5.0;


using namespace std;
using namespace sf;

class StatusBarFunctions
{
public:
	virtual void OpenMenu()=0;
};

enum class Icons
{
    MONEY, ARMIES, CITIES, ROUNDS
};

class Statusbar : public IClickable, public IDrawable, public IAnimatable, public IButtonfunction
{
	

private: // soll eigentlich NICHT abgeleitet werden
	bool m_mouseOver;
	Vector2f m_MousePos;

	//Grundeigenschaften

	//angezeigte Elemente
	RectangleShape m_BaseRect; // Hintergrund
	StandardButton* m_BMenu;
	vector<String> m_vTexturenames;
	vector<Texture> m_vTextures;
	vector<Sprite> m_vSPictures;
	vector<Textblock*> m_vTLabels;

	//Zeiger auf andere Klassen
	StatusBarFunctions* m_pOpenMenu;

public:
	vector<int> m_vValue;
	//ctor & dtor
	Statusbar(Vector2f pos, Vector2f size, StatusBarFunctions* OpenMenu);
	~Statusbar(void);
	void preload_Textures();
	//Setter & Getter
	void setMouse(Vector2f pos);
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	void setBgColor(Color c);
	void Resize(Vector2f new_size);
	void setValue(Icons icon, int value);
	void increaseValue(Icons icon, int value);
	void decreaseValue(Icons icon, int value);
	//Containerverwaltung
	//void Push(

	//IClickable
	virtual bool MouseMoved(sf::Vector2i &);
	virtual bool PressedRight();
	virtual bool PressedLeft();
	virtual bool ReleasedRight();
	virtual bool ReleasedLeft();
	//IDrawable
	virtual void draw(sf::RenderWindow* rw);
	//IAnimatable
	virtual void animationTick();
	//IButtonFunktion
	void onButtonClick(int);
};

