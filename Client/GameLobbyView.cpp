#include "GameLobbyView.h"

GameLobbyView::GameLobbyView(Vector2u & screensize)
{

	this->players[0] = new Textblock(sf::Vector2f(10, 10),sf::Vector2f(100, 20), "player1", 25);
	m_DrawV.push_back(this->players[0]);
	this->players[1] = new Textblock(sf::Vector2f(10,50),sf::Vector2f(100, 20), "player2", 25);
	m_DrawV.push_back(this->players[1]);
	this->players[2] = new Textblock(sf::Vector2f(10,100),sf::Vector2f(100, 20), "player3", 25);
	m_DrawV.push_back(this->players[2]);
	this->players[3] = new Textblock(sf::Vector2f(10,150),sf::Vector2f(100, 20), "", 25);
	this->players[3]->setBackgroundColor(MyColors.Transparent);
	m_DrawV.push_back(this->players[3]);

	this->mapName = new Textblock(sf::Vector2f(10, 200), sf::Vector2f(50, 20), "mapname", 25);
	m_DrawV.push_back(mapName);

	this->kickPlayer[0] = new StandardButton(sf::Vector2f(10, 250), sf::Vector2f(20, 10), "kick", KICKP1, false); 
	this->kickPlayer[1] = new StandardButton(sf::Vector2f(40, 250), sf::Vector2f(20, 10), "kick", KICKP2, false); 
	this->kickPlayer[2] = new StandardButton(sf::Vector2f(70, 250), sf::Vector2f(20, 10), "kick", KICKP3, false); 
	this->leave = new StandardButton(sf::Vector2f(10, 280), sf::Vector2f(20, 10), "leave", LEAVE, false);
	this->startgame = new StandardButton(sf::Vector2f(50, 280), sf::Vector2f(20, 10), "start", START, false);

	for (int i = 0; i < 3; i++)
	{
		m_DrawV.push_back(kickPlayer[i]);
		m_AnimateV.push_back(kickPlayer[i]);
		m_ClickV.push_back(kickPlayer[i]);
	}

	this->kickPlayer[0]->Attach(this);
	this->kickPlayer[1]->Attach(this);
	this->kickPlayer[2]->Attach(this);

	m_DrawV.push_back(leave);
	m_AnimateV.push_back(leave);
	m_ClickV.push_back(leave);
	this->leave->Attach(this);

	m_DrawV.push_back(startgame);
	m_AnimateV.push_back(startgame);
	m_ClickV.push_back(startgame);
	this->startgame->Attach(this);
	
	
	m_nextView = Views::NOCHANGE;

	centering(screensize);

}

GameLobbyView::~GameLobbyView()
{
	for (int i = 0; i < 4; i++)
		delete this->players[i];
	
	delete this->mapName;
	delete this->kickPlayer[0];
	delete this->kickPlayer[1];
	delete this->kickPlayer[2];
	delete this->leave;
	delete this->startgame;
}


void GameLobbyView::onButtonClick(int id)
{
	switch(id)
	{
		case LEAVE:
			{
				break;
			}
		case START:
			{
				break;
			}
		case KICKP1:
			{
				break;
			}
		case KICKP2:
			{
				break;
			}
		case KICKP3:
			{
				break;
			}
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

}

Views GameLobbyView::nextState()
{
	return m_nextView;
}

void GameLobbyView::pt1zyklisch(double elpasedMs)
{
	//BURAK GOES HERE
	//this gets info from the server 
}

void GameLobbyView::onResize(Vector2u & size)
{
	centering(size);
}

Views GameLobbyView::getType()
{
	return Views::GAMELOBBY;
}


void GameLobbyView::centering(Vector2u & size)
{

}

