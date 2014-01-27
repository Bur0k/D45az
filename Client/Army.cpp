#include "Army.h"

Army::Army()
{
	
}

Army::Army(int i)
{
	m_animation = -1;
	m_mouseOver = false;
	m_animating = false;

	
}

Army::~Army()
{

}

void Army::PositionGraphics()
{
	//set the position of graphic objects
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
	if(m_animation > 0)
	{
		m_animation --;
		float ratio = static_cast<float>(m_animation) / ARMY_ANIMATIONSTEPS;	
		Vector2f currentPos = m_oldPos * ratio + m_targetPos * (1 - ratio);
		m_dimensions.left = currentPos.x;
		m_dimensions.top = currentPos.y;

		PositionGraphics();

		if(m_animation == 0)
			m_animating = false;
	}
}

Vector2i Army::getPosition()
{
	return m_position;
}

void Army::setPosition(Vector2i pos)
{
	move(pos - m_position);
}

void Army::move(Vector2i delta)
{
	m_dimensions.left = static_cast<float>(m_Tilesize.x * (delta.x + m_position.x) -  m_mapViewOffset.x);
	m_dimensions.top = static_cast<float>(m_Tilesize.y * (delta.y + m_position.y) -  m_mapViewOffset.y);
	m_position += delta;

	PositionGraphics();
}


bool Army::animatedMove(Vector2i target)
{
	if(m_animating)	//if animation is running return false;
		return false;

	m_animation = ARMY_ANIMATIONSTEPS + 1;
	m_animating = true;
	m_oldPos = Vector2f(m_dimensions.left,m_dimensions.top);
	m_targetPos = Vector2f( static_cast<float>(target.x * m_Tilesize.x),
							static_cast<float>(target.y * m_Tilesize.y));


	return true;
}

ingameObjectType Army::getType()
{
	return ingameObjectType::ARMY;
}

void /* TODO NOT VOID but info pointer to army*/ Army::getArmy()
{

}

void /* TODO NOT VOID but info pointer to city*/ Army::getCity()
{

}
