#include "IngameMainGui.h"


IngameMainGuy::IngameMainGuy(Vector2u & screensize)
{

}

IngameMainGuy::~IngameMainGuy()
{
	
}

void IngameMainGuy::onButtonClick(int id)
{
	switch (id)
	{
	default:
		break;
	}
}

void IngameMainGuy::onSliderValueChange(int ID, double position)
{
	//DO SOMETHING
}

void IngameMainGuy::onSliderReleased(int ID, double position)
{
	//DO SOMETHING
}

void IngameMainGuy::onTextBoxSend(int ID, std::string s)
{

}



bool IngameMainGuy::MouseMoved(sf::Vector2i & mouse)
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->MouseMoved(mouse))
			return true;
	return false;
}

bool IngameMainGuy::PressedRight()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedRight())
			return true;
	return false;
}

bool IngameMainGuy::PressedLeft()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedLeft())
			return true;
	return false;
}

bool IngameMainGuy::ReleasedRight()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->ReleasedRight())
			return true;
	return false;
}

bool IngameMainGuy::ReleasedLeft()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->ReleasedLeft())
			return true;
	return false;
}
	
void IngameMainGuy::animationTick()
{
	for(unsigned int i = 0; i < m_AnimateV.size(); i++)
		m_AnimateV[i]->animationTick();
}
	
void IngameMainGuy::onKeyDown(sf::Event e)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onKeyDown(e);
}

void IngameMainGuy::onKeyUp(sf::Event e)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onKeyUp(e);
}
void IngameMainGuy::onTextInput(std::string s)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onTextInput(s);
}

void IngameMainGuy::draw(sf::RenderWindow* rw)
{
	for(unsigned int i = 0; i < m_DrawV.size(); i++)
		m_DrawV[i]->draw(rw);	
}

void IngameMainGuy::onResize(sf::Vector2u &)
{

}