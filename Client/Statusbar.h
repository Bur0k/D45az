#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

#include "IClickable.h"
#include "graphic_globals.h"
#include "IDrawable.h"
#include "IAnimatable.h"

#include "StandardButton.h"
#include "Textbox.h"
#include "Game.h"

#define AbstandX 5

using namespace std;


class Statusbar : public IClickable, public IDrawable, public IAnimatable
{
private: // soll eigentlich NICHT abgeleitet werden
	bool m_mouseOver;
	Vector2f m_MousePos;

	//Grundeigenschaften
	RectangleShape m_BaseRect; // Hintergrund
	StandardButton* m_BMenu;
	vector<TextBox> m_TextboxContainer;

public:
	//ctor & dtor
	Statusbar(Vector2f pos, Vector2f size, Game* game);
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
};

