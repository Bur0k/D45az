#include "Button.h"


Button::Button(Vector2f pos, Vector2f size, sf::String S)
{
	m_animation = 0;
	m_isEnabled = false;
	m_isClicked = false;
	m_backgroundRect.setSize(size);
	m_backgroundRect.setPosition(pos);
	Font f;
	//TODO auslagern!!!!
	f.loadFromFile("Data/Fonts/arial.ttf");
	m_buttonText.setFont(f);
	m_buttonText.setString(S);


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
	m_buttonText = b.m_buttonText;
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
	return m_backgroundRect.getPosition();
}


bool Button::isHit(Vector2f mouse)
{
	if( mouse.x > m_backgroundRect.getPosition().x && mouse.x < m_backgroundRect.getPosition().x + m_backgroundRect.getSize().x &&
		mouse.y > m_backgroundRect.getPosition().y && mouse.y < m_backgroundRect.getPosition().y + m_backgroundRect.getSize().y )
		return true;
	else
		return false;
}

void Button::draw(RenderWindow* rw)
{
	rw->draw(m_backgroundRect);
	rw->draw(m_buttonText);
}

void Button::animationTick(bool dir)
{
	
}