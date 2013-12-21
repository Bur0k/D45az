#ifndef ICLICKABLE_H
#define ICLICKABLE_H

#include <SFML\Graphics.hpp>

class IClickable
{
public:
	virtual bool isHit(sf::Vector2i &)=0;
	virtual void PressedRight()=0;
	virtual void  PressedLeft()=0;
	virtual void  ReleasedRight()=0;
	virtual void  ReleasedLeft()=0;
};

#endif