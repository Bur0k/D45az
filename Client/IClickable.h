#ifndef ICLICKABLE_H
#define ICLICKABLE_H

#include <SFML\Graphics.hpp>
#include <vector>


//interface for all mouse related functions
class IClickable
{
public:
	virtual bool isHit(sf::Vector2i &)=0;
	virtual void PressedRight()=0;
	virtual void PressedLeft()=0;
	virtual void ReleasedRight()=0;
	virtual void ReleasedLeft()=0;
};

typedef std::vector<IClickable*> ClickList;

#endif