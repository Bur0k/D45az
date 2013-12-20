#include "Button.h"


Button::Button(Vector2f pos, Vector2f size)
{
	m_animation = 0;
	m_isEnabled = false;
	m_isClicked = false;
	m_backgroundRect.setSize(size);
	m_backgroundRect.setPosition(pos);
}

Button::~Button()
{
	
}

Button::Button(const Button & b)
{
	m_backgroundRect.setSize(b.m_backgroundRect.getSize());
	m_backgroundRect.setPosition(b.m_backgroundRect.getPosition());
	m_animation = b.m_animation;
	m_isEnabled = b.m_isEnabled;
	m_isClicked = b.m_isClicked;
	for(unsigned int i = 0; i < m_attachedFunctions.size(); i++)
		m_attachedFunctions.push_back(m_attachedFunctions[i]);
}

void Button::setIsEnabled(bool enable)
{
	m_isEnabled = enable;
}

bool Button::getIsEnabled()
{
	return m_isEnabled;
}

void Button::setSize(Vector2f size)
{
	m_backgroundRect.setSize(size);
}

Vector2f Button::getSizze()
{
	return m_backgroundRect.getSize();
}

void Button::setPosition(Vector2f pos)
{
	m_backgroundRect.setPosition(pos);
}

Vector2f Button::getPosition()
{
	return m_position;
}


bool Button::isHit(Vector2f mouse)
{
	if( mouse.x > m_position.x && mouse.x < m_position.x + m_size.x &&
		mouse.y > m_position.y && mouse.y < m_position.y + m_size.y )
		return true;
	else
		return false;
}

void Button::draw(RenderWindow* rw)
{
	m_backgroundRect.setSize(m_size);
	m_backgroundRect.setPosition(m_position);
	rw->draw(r);
}

void Button::animationTick()
{
	
}