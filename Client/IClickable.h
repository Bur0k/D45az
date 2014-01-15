#ifndef ICLICKABLE_H
#define ICLICKABLE_H

#include <SFML\Graphics.hpp>
#include <vector>


//interface for all mouse related functions
class IClickable
{
public:
	virtual bool MouseMooved(sf::Vector2i &)=0;
	virtual bool PressedRight()=0;
	virtual bool PressedLeft()=0;
	virtual bool ReleasedRight()=0;
	virtual bool ReleasedLeft()=0;
};

typedef std::vector<IClickable*> ClickVect;

#endif