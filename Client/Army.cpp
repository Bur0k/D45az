#include "Army.h"

Army::Army()
{

}

Army::Army(int i)
{

}

Army::~Army()
{

}

//IDrawable
void Army::draw(sf::RenderWindow* rw)
{
	if(!m_inCity)
	{
		if(m_marked)
			rw->draw(m_markedIndicator);
		rw->draw(m_body);
	}
	rw->draw(m_powerBar);
	rw->draw(m_flag);
}
//IClickable
bool Army::MouseMoved(sf::Vector2i & mouse)
{
	if( mouse.x > m_dimensions.left && mouse.x < m_dimensions.left + m_dimensions.width &&
		mouse.x > m_dimensions.left && mouse.x < m_dimensions.left + m_dimensions.width)
		m_mouseOver = true;
	else	
		m_mouseOver = true;
	
	return m_mouseOver;
}

bool Army::PressedLeft()
{
	if(m_mouseOver)
	{
		m_marked = !m_marked;
		return true;
	}
	else 
		return false;
}

bool Army::PressedRight(){ return false; }
bool Army::ReleasedRight(){ return false; }
bool Army::ReleasedLeft(){ return false; }



void Army::animationTick()
{
	
}

Vector2i Army::getPosition()
{
	return m_position;
}

void Army::setPosition(Vector2i pos)
{
	m_dimensions.left = m_Tilesize.x * pos.x -  m_mapViewOffset.x;
	m_dimensions.top = m_Tilesize.y * pos.y -  m_mapViewOffset.y;
}

void Army::move(Vector2i pos)
{
	m_animation = ARMY_ANIMATIONSTEPS;
	m_animating = true;

}
