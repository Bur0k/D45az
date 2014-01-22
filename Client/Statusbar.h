#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

#include "IClickable.h"
#include "graphic_globals.h"
#include "IDrawable.h"
#include "IAnimatable.h"

#include "StandardButton.h"
#include "Textblock.h"

#define Elementlength 60
#define Statusbarheight 50

using namespace std;
using namespace sf;

class StatusBarFunctions
{
public:
	virtual void OpenMenu()=0;
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
	Texture m_Ttmp;
	Sprite* m_SGold;
	Textblock* m_TBGold;
	vector<Sprite*> m_vSPictures;
	vector<Textblock*> m_vTLabels;

	//Zeiger auf andere Klassen
	StatusBarFunctions* m_pOpenMenu;

public:
	//ctor & dtor
	Statusbar(Vector2f pos, Vector2f size, StatusBarFunctions* OpenMenu);
	~Statusbar(void);
	//Setter & Getter
	void setMouse(Vector2f pos);
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	void setBgColor(Color c);
	void Resize(Vector2f new_size);
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

