#include "GameLobbyView.h"

GameLobbyView::GameLobbyView(Vector2u & screensize)
{
	
	
}

GameLobbyView::~GameLobbyView()
{
	
}


void GameLobbyView::onButtonClick(int id)
{
	switch (id)
	{
	default:
		break;
	}
}

void GameLobbyView::onSliderValueChange(int ID, double position)
{
	//DO SOMETHING
}

void GameLobbyView::onSliderReleased(int ID, double position)
{
	//DO SOMETHING
}

void GameLobbyView::onTextBoxSend(int ID, std::string s)
{

}



bool GameLobbyView::MouseMoved(sf::Vector2i & mouse)
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->MouseMoved(mouse))
			return true;
	return false;
}

bool GameLobbyView::PressedRight()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedRight())
			return true;
	return false;
}

bool GameLobbyView::PressedLeft()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedLeft())
			return true;
	return false;
}

bool GameLobbyView::ReleasedRight()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->ReleasedRight())
			return true;
	return false;
}

bool GameLobbyView::ReleasedLeft()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->ReleasedLeft())
			return true;
	return false;
}
	
void GameLobbyView::animationTick()
{
	for(unsigned int i = 0; i < m_AnimateV.size(); i++)
		m_AnimateV[i]->animationTick();
}
	
void GameLobbyView::onKeyDown(sf::Event e)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onKeyDown(e);
}

void GameLobbyView::onKeyUp(sf::Event e)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onKeyUp(e);
}
void GameLobbyView::onTextInput(std::string s)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onTextInput(s);
}

void GameLobbyView::draw(sf::RenderWindow* rw)
{
	for(unsigned int i = 0; i < m_DrawV.size(); i++)
		m_DrawV[i]->draw(rw);	
	
	Rect<float> MapView;

}

Views GameLobbyView::nextState()
{
	return m_nextView;
}

void GameLobbyView::update(double elpasedMs)
{
	//BURAK GOES HERE
	//this gets info from the server 
}

void GameLobbyView::onResize(Vector2u & size)
{
	
}

Views GameLobbyView::getType()
{
	return Views::;
	//noch nicht fertig
	asdf
}

