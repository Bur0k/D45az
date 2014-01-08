#include "Button.h"

//TODO eingerasteten button bauen

Button::Button()
{
	//TODO
}

Button::Button(Vector2f pos, Vector2f size, sf::String S, int ID, bool lock)
{
	m_animation = 0;
	m_animationLength = 15;
	m_ID = ID;

	m_isEnabled = true;
	m_isClicked = false;
	m_mouseOver = false;
	m_staysClicked = lock;
	m_lockedIn = false;
	
	setSize(size);
	setPosition(pos);
	m_Font = Font(MyFonts.Arial);
	m_buttonText.setFont(m_Font);
	m_buttonText.setString(S);
	
	m_buttonText.setColor(MyColors.Black);

	
	
	//fit the text into the button
	fitText(0);
	
	//std::cout << "textsize x " << textsize.width << " y " << textsize.height << std::endl;
	
	m_color = MyColors.White;
	setFillColor(m_color);
	m_color_clicked = MyColors.Orange;
	m_color_mouseOver = MyColors.Red;
	m_color_disabled = MyColors.Gray;
	
}

Button::~Button()
{
	m_attachedFunctions.clear();
}

Button::Button(const Button & b)
{
	*this = b;
	//TODO complete
	
}

void Button::operator=(const Button & b)
{
	setSize(b.getSize());
	setPosition(b.getPosition());

	m_animation = b.m_animation;
	m_animationLength = b.m_animationLength;
	m_ID = b.m_ID;

	m_isEnabled = b.m_isEnabled;
	m_isClicked = b.m_isClicked;
	m_staysClicked = b.m_staysClicked;
	m_lockedIn = b.m_lockedIn;
	m_mouseOver = b.m_mouseOver;

	m_color = b.m_color;
	m_color_mouseOver = b.m_color_mouseOver;
	m_color_clicked = b.m_color_clicked;
	m_color_disabled = b.m_color_disabled;

	m_buttonText = b.m_buttonText;

	for(unsigned int i = 0; i < m_attachedFunctions.size(); i++)
		m_attachedFunctions.push_back(m_attachedFunctions[i]);
}

void Button::fitText(int border)
{
	m_buttonText.setPosition(getPosition());

	sf::Rect<float> textsize;
	Vector2f size = this->getSize();

	textsize = m_buttonText.getLocalBounds();
	float scale = m_buttonText.getScale().x;
	if(textsize.width * scale > size.x - border * 2)
	{
		scale = (float)(size.x - border * 2) / textsize.width;
		m_buttonText.setScale(scale, scale);
	}

	textsize = m_buttonText.getLocalBounds();
	if(textsize.height * scale > size.y - border * 2)
	{
		scale = (float)(size.y - border * 2) / textsize.height;
	}

	m_buttonText.move(	(getSize().x - textsize.width * m_buttonText.getScale().x) / 2.0f,
						(getSize().y - textsize.height * 1.5f * m_buttonText.getScale().y) / 2.0f);
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

bool Button::getIsPressed()
{

	return m_isClicked;
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
		if(!m_lockedIn)			
			m_isClicked = false;
		
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
		if(m_staysClicked)
			m_lockedIn = (m_lockedIn)? false : true;
	}
}

void Button::ReleasedLeft()
{
	if(m_isClicked)
	{	
		if(!m_lockedIn)
		{
			m_isClicked = false;
			unclicked();
		}
		notify();
	}
}


void Button::setScale(Vector2f){}
void Button::setScale(float x, float y){}
void Button::PressedRight(){}
void Button::ReleasedRight(){}

void Button::draw(RenderWindow* rw)
{
	rw->draw(*this);
	rw->draw(m_buttonText);
}

void Button::animationTick()
{
	if(m_isEnabled && !m_isClicked)
	{
		//std::cout << "Animation Count : " << m_animation << std::endl;
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

	double ratio1 =  sqrt((double)m_animation) / sqrt((double)m_animationLength);
	double ratio2 = 1 - ratio1;
	setFillColor(Color( (Uint8)(c.r * ratio1 + m_color.r * ratio2),
						(Uint8)(c.g * ratio1 + m_color.g * ratio2),
						(Uint8)(c.b * ratio1 + m_color.b * ratio2),
						(Uint8)(c.a * ratio1 + m_color.a * ratio2)));
	
	updateVisuals();
}

void Button::updateVisuals()
{
	//implementation in derived classes
}

void Button::clicked()
{
	if(m_isClicked)
	{
		setFillColor(m_color_clicked);
		updateVisuals();
	}
}

void Button::unclicked()
{
	if(!m_isClicked)
		animation_upadate();
}

bool Button::attachFunction(IButtonfunction* pCallback)
{
	//TODO no double attachments
	m_attachedFunctions.push_back(pCallback);
	return true;
}

bool Button::detachFunction(IButtonfunction* pCallback)
{
	for(unsigned int i = 0; i < m_attachedFunctions.size(); i++)
		if(m_attachedFunctions[i] == pCallback)
		{
			m_attachedFunctions.erase(m_attachedFunctions.begin() + i);
			return true;
		}
	return false;
}

void Button::notify()
{
	for(unsigned int i = 0; i < m_attachedFunctions.size(); i++)
	{
		m_attachedFunctions[i]->onButtonClick(m_ID);
	}
}

