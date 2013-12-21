#include "Button.h"

//TODO eingerasteten button bauen

Button::Button()
{
	//TODO
}

Button::Button(Vector2f pos, Vector2f size, sf::String S)
{
	m_animation = 0;
	m_animationLength = 15;

	m_isEnabled = true;
	m_isClicked = false;
	m_mouseOver = false;
	
	setSize(size);
	setPosition(pos);
	
	//TODO auslagern!!!!
	Font f;
	f.loadFromFile("Data/Fonts/arial.ttf");

	m_buttonText.setFont(f);
	m_buttonText.setString(S);
	m_buttonText.setPosition(getPosition());


	m_color = Color(0xFF, 0xFF, 0xFF, 0xFF);
	setFillColor(m_color);
	m_color_clicked = Color(0xFF, 0xA2, 0x00, 0xFF);
	m_color_mouseOver = Color(0x00, 0xFF, 0x6A, 0xFF);
	m_color_disabled = Color(0x80, 0x80, 0x80, 0xFF);

}

Button::~Button()
{
	
}

Button::Button(const Button & b)
{
	//TODO complete
	setSize(b.getSize());
	setPosition(b.getPosition());
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
	if(!enable)
		setFillColor(m_color_disabled);
}

bool Button::getIsEnabled()
{
	return m_isEnabled;
}

bool Button::isHit(Vector2i & mouse)
{
	//std::cout << "mouse position x " << mouse.x << " y " << mouse.y; 
	if( mouse.x > getPosition().x && mouse.x < getPosition().x + getSize().x &&
		mouse.y > getPosition().y && mouse.y < getPosition().y + getSize().y )
	{
		m_mouseOver = true;
		return true;
	}
	else 
	{
		m_mouseOver = false;
		return false;
	}
}

void Button::PressedLeft()
{
		if(m_mouseOver)
	{
		m_animation = m_animationLength;
		m_isClicked = true;
		clicked();
	}
}

void Button::ReleasedLeft()
{
	if(m_isClicked)
	{
		m_isClicked = false;
		notify();
		unclicked();
	}
}

void Button::PressedRight(){}
void Button::ReleasedRight(){}

void Button::draw(RenderWindow* rw)
{
	rw->draw(*this);
	//rw->draw(m_buttonText);
}

void Button::animationTick()
{
	if(m_isEnabled && !m_isClicked)
	{
		if(m_mouseOver && m_animation < m_animationLength)
		{
			m_animation++; 
			animation_upadate();	
		}
		else if(m_animation > 0 && !m_mouseOver)
		{
			m_animation--;
			animation_upadate();
		}
	}
}

//example implementation
void Button::animation_upadate()
{
	Color c = m_color_mouseOver;

	double ratio1 =  (double)(m_animation * m_animation)/ (double)(m_animationLength *m_animationLength); 
	double ratio2 = 1 - ratio1;
	setFillColor(Color( (Uint8)(c.r * ratio1 + m_color.r * ratio2),
						(Uint8)(c.g * ratio1 + m_color.g * ratio2),
						(Uint8)(c.b * ratio1 + m_color.b * ratio2),
						(Uint8)(c.a * ratio1 + m_color.a * ratio2)));
}

void Button::clicked()
{
	if(m_isClicked)
		setFillColor(m_color_clicked);
}

void Button::unclicked()
{
	if(!m_isClicked)
		animation_upadate();
}

bool Button::attachFunction(callback_func pfunc)
{
	//TODO no double attachments
	m_attachedFunctions.push_back(pfunc);
	return true;
}

bool Button::detachFunction(callback_func pfunc)
{
	for(unsigned int i = 0; i < m_attachedFunctions.size(); i++)
		if(m_attachedFunctions[i] == pfunc)
		{
			m_attachedFunctions.erase(m_attachedFunctions.begin() + i);
			return true;
		}
	return false;
}

void Button::notify()
{
	for(unsigned int i = 0; i < m_attachedFunctions.size(); i++)
		m_attachedFunctions[i]();
}

