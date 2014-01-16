#include "Statusbar.h"


Statusbar::Statusbar(Vector2f pos, Vector2f size)
{/*
	setPosition(pos);
	m_Font = Font(MyFonts::getFont(GameFonts::ARIAL));
	m_textblockText.setFont(m_Font);
	m_textblockText.setPosition(getPosition());
	m_textblockText.setColor(MyColors.Black);
	m_textblockText.setCharacterSize(CharSize);
	m_textblockText.setString(lineBreak(S, size));
	textsize = m_textblockText.getLocalBounds();
	this->setSize(Vector2f(textsize.width + 5, textsize.height + 10));
	m_color = MyColors.Gray;
	setFillColor(m_color);
	fixCharsize();
	*/
}


Statusbar::~Statusbar(void)
{
}

Vector2f Statusbar::getPosition()
{
	return Vector2f(m_dimensions.left, m_dimensions.top);
}

void Statusbar::setPosition(Vector2f){}

bool Statusbar::MouseMooved(sf::Vector2i & mouse)
{
	//checken ob maus nach einer bewegung auf der statusbar ist
	if( mouse.x >= m_dimensions.left && mouse.x <= m_dimensions.left + m_dimensions.width &&
		mouse.y >= m_dimensions.top && mouse.y <= m_dimensions.top + m_dimensions.height)
		m_mouseOver = true;
	else
		m_mouseOver = false;

	return m_mouseOver;
}

bool Statusbar::PressedLeft()
{
	if(m_mouseOver && !m_inFocus) //TODO verschiedene objekte müssen anwählbar sein
	{
		m_inFocus = true;
	}
	else if(m_inFocus && m_mouseOver)
		return true;
	else if(!m_mouseOver)
		m_inFocus = false;

	return false;
}

bool Statusbar::ReleasedLeft(){ return false; }
bool Statusbar::PressedRight(){ return false; }
bool Statusbar::ReleasedRight(){ return false; }

void Statusbar::animationTick() // IAnimation
{
}

void Statusbar::draw(sf::RenderWindow* rw) // IDrawable
{
	rw->draw(m_BaseRect);
	if(m_inFocus) 
		rw->draw(m_cursor);

	for(int i = 0; i < 8; i++)
		rw->draw(m_pBorder[i].s);

	//TODO draw nice graphics around m_BaseRect
}
