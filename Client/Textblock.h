#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

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

class Textblock : public IDrawable, public RectangleShape
{
public:
	Textblock();
	Textblock(Vector2f pos, Vector2f size, String S, int CharSize);
	~Textblock();
	void operator=(const Textblock & tblock);

protected:
	Text m_textblockText;
	int m_ID;
	Font m_Font;
	Color m_color;
	sf::Rect<float> textsize;
public:
	virtual void draw(RenderWindow* rw);
	std::string lineBreak(String S, Vector2f size);
	void setText(String S, Vector2f size);
	void setPosition(Vector2f pos);
	void setFontColor(Color color);
};


#endif