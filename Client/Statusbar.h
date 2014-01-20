#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

#include "IClickable.h"
#include "graphic_globals.h"
#include "IDrawable.h"
#include "IAnimatable.h"

#include "Button.h"
#include "Textbox.h"

using namespace std;


class Statusbar : public IClickable, public IDrawable, public IAnimatable
{
private: // soll eigentlich NICHT abgeleitet werden
	bool m_inFocus;
	bool m_mouseOver;

	//Grundeigenschaften
	RectangleShape m_BaseRect; // Hintergrund
	vector<Button> m_ButtonContainer;
	vector<TextBox> m_TextboxContainer;

public:
	//ctor & dtor
	Statusbar(Vector2f pos, Vector2f size);
	~Statusbar(void);
	//Setter & Getter
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

