#ifndef SLIDER_H
#define SLIDER_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <vector>

#include "IClickable.h"
#include "IDrawable.h"
#include "graphic_globals.h"	


using namespace sf;

//#define SLIDERENDBLOCKWIDTH 10

static const float SLIDERENDBLOCKWIDTH = 10;

class ISliderFunction
{
public:
	virtual void onSliderValueChange(int ID, double position)=0;
	virtual void onSliderReleased(int ID, double position)=0;
};

typedef std::vector<ISliderFunction*> SliderCallbackTarget;

class Slider : public IClickable, public IDrawable
{
protected:
	sf::Rect<float> m_dimensions;
	int m_ID;
	SliderCallbackTarget m_attachedFunctions;
	Vector2f m_position;
	Vector2f m_size;
	bool m_horizontal;
	bool m_mouseOver;
	bool m_mouseDown;
	bool m_wasClicked;
	
	SpriteTex* m_pBar;


	Vector2i m_oldMouse;

	
	void Notify();

public:
	//@param startsliderposition value from 0 to 1
	Slider(bool horizontal, Vector2f size, double startsliderposition, Vector2f pos, int id);
	~Slider();


	void Attach(ISliderFunction*);
	bool Detach(ISliderFunction*);
	
	double getValue();
	void setValue(double);

	void setPosition(Vector2f);
	Vector2f getPosition();
	void move(Vector2f);

	//Implementation of IClickable

	bool MouseMoved(Vector2i &);
	bool PressedRight();
	bool PressedLeft();
	bool ReleasedRight();
	bool ReleasedLeft();

	void draw(RenderWindow* rw);
	
};

#endif