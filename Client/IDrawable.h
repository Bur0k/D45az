#ifndef IDRAWABLE_H
#define IDRAWABLE_H
#include <vector>
#include <SFML\Graphics.hpp>


class IDrawable
{
public:
	virtual void draw(sf::RenderWindow* rw)=0;
};


typedef std::vector<IDrawable*> DrawStack;

#endif