#include "Statusbar.h"

//Ctro & Dtor-------------------------------------------------------
Statusbar::Statusbar(Vector2f pos, Vector2f size)
{
	m_BaseRect.setPosition(pos);
	m_BaseRect.setSize(size);
	m_BaseRect.setFillColor(MyColors.Black);
}


Statusbar::~Statusbar(void)
{
}

//Getter & Setter-------------------------------------------------------
Vector2f Statusbar::getPosition()
{
	return Vector2f(m_dimensions.left, m_dimensions.top);
}

void Statusbar::setPosition(Vector2f pos)
{
	m_dimensions.left += pos.x;
	m_dimensions.top += pos.y;
}

void Statusbar::setBgColor(Color c)
{
	m_BaseRect.setFillColor(c);
}

void Statusbar::Resize(Vector2f new_size)
{
	m_BaseRect.setSize(new_size);
}

//Hilfsfunktionen-------------------------------------------------------




//Interface-Funktionen-------------------------------------------------------
bool Statusbar::MouseMoved(sf::Vector2i & mouse)
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
	//TODO draw nice graphics around m_BaseRect
}
