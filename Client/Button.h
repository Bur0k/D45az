#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "IDrawable.h"
using namespace sf;


typedef std::vector<void (*) (void)> FuncPointerVect;

// implements basic button functionality
// derived classes should implement visuals
class Button : public IDrawable
{
protected:
	Button(Vector2f pos, Vector2f size);
	Button(const Button & b);
	~Button();

	FuncPointerVect m_attachedFunctions;
	RectangleShape m_backgroundRect;
	int m_animation;
	bool m_isEnabled;
	//to avoid spamming attached functions
	bool m_isClicked;
	
public:
	void setIsEnabled(bool enable);
	bool getIsEnabled();

	void setSize(Vector2f size);
	Vector2f getSizze();

	void setPosition(Vector2f pos);
	Vector2f getPosition();

	//changes color of the background Rectangle
	//@param dir true if mouse is over the button
	void animationTick(bool dir);


	//implementing IDrawable
	virtual void draw(RenderWindow* rw);

	bool isHit(sf::Vector2f);

	//attaching a function pointer 
	bool attachFunction(void (*pfunc)(void));
	//detaching a function pointer
	bool detachFunction(void (*pfunc)(void));

};


#endif