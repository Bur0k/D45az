#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>

#include "IDrawable.h"
#include "IClickable.h"
#include "graphic_globals.h"
#include "IButtonfunction.h"
#include "IAnimatable.h"

using namespace sf;

typedef std::vector<IButtonfunction*> FuncPointerVect;

// implements basic button functionality
// derived classes should implement visuals
class Button : public IDrawable, public RectangleShape, public IClickable, public IAnimatable
{
public:
	//TODO standadconstructor
	Button();
	Button(Vector2f pos, Vector2f size, sf::String S, int ID, bool lock);
	Button(const Button & b);
	~Button();
	void operator=(const Button & b);
protected:
	FuncPointerVect m_attachedFunctions;
	Text m_buttonText;
	
	//gets returned in the notify function
	int m_ID;
	int m_animation;
	int m_animationLength;

	bool m_isEnabled;
	//to avoid spamming attached functions
	bool m_isClicked;
	//if true button stays activated till clicked again or click somewhere else
	bool m_staysClicked;
	bool m_lockedIn;

	bool m_mouseOver;

	Font m_Font;

	Color m_color;
	Color m_color_mouseOver;
	Color m_color_clicked;
	Color m_color_disabled;


	//is called when button is clicked to change the buttons appearance
	virtual void clicked();
	virtual void unclicked();

	//is called by animatioTick() to update the button color
	virtual void animation_upadate();

	//for derived classes to update their visuals
	virtual void updateVisuals(bool colorChange);

public:
	void setIsEnabled(bool enable);
	bool getIsEnabled();

	//changes color of the background Rectangle
	//@param dir true if mouse is over the button
	void animationTick();
	
	

	//implementing IDrawable
	virtual void draw(RenderWindow* rw);

	//implementing IClickable
	bool isHit(Vector2i &);
	void  PressedRight();
	void  PressedLeft();
	void  ReleasedRight();
	void  ReleasedLeft();

	//attaching a function pointer 
	bool attachFunction(IButtonfunction* pCallback);
	//detaching a function pointer
	bool detachFunction(IButtonfunction* pCallback);
	//
	void notify();


};


#endif