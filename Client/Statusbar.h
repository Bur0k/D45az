#pragma once


#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

#include "IClickable.h"
#include "graphic_globals.h"
#include "IDrawable.h"
#include "IAnimatable.h"


class Statusbar : public IClickable, public IDrawable, public IAnimatable
{
private: // soll eigentlich NICHT abgeleitet werden
	bool m_inFocus;
	bool m_mouseOver;

	//Grundeigenschaften
	Rect<float> m_dimensions;
	RectangleShape m_BaseRect;

	//komische Sachen
	RectangleShape m_cursor;
	SpriteTex* m_pBorder;

public:
	//ctor & dtor
	Statusbar(Vector2f pos, Vector2f size);
	~Statusbar(void);
	//Setter & Getter
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	void setBgColor(Color c);
	void Resize(Vector2f new_size);
	//Hilfsfunktionen

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

