#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "IDrawable.h"
#include "IClickable.h"
#include <iostream>
using namespace sf;

typedef void (*callback_func)(void);
typedef std::vector<callback_func> FuncPointerVect;

// implements basic button functionality
// derived classes should implement visuals
class Button : public IDrawable, public RectangleShape, public IClickable
{
public:
	//TODO standadconstructor
	Button();
	Button(Vector2f pos, Vector2f size, sf::String S);
	Button(const Button & b);
	~Button();
protected:
	FuncPointerVect m_attachedFunctions;
	Text m_buttonText;
	
	int m_animation;
	int m_animationLength;

	bool m_isEnabled;
	//to avoid spamming attached functions
	bool m_isClicked;
	//if true button stays activated till clicked again or click somewhere else
	bool m_staysClicked;

	bool m_mouseOver;

	Color m_color;
	Color m_color_mouseOver;
	Color m_color_clicked;
	Color m_color_disabled;


	//is called when button is clicked to change the buttons appearance
	virtual void clicked();
	virtual void unclicked();

	//is called by animatioTick() to update the button color
	virtual void animation_upadate();

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
	bool attachFunction(callback_func pfunc);
	//detaching a function pointer
	bool detachFunction(callback_func pfunc);
	//
	void notify();


};


#endif