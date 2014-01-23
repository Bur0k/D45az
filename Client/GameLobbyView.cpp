#include "GameLobbyView.h"

GameLobbyView::GameLobbyView(Vector2u & screensize)
{
	this->game = new GameLobby();

	if (playerData.Name == game->gameMaster)
	{
		amIGamemaster = true;
		//this->playernumber = 1;
	}
	else
	{
		amIGamemaster = false;
	}

	for (unsigned int i = 0; i < this->game->players.size(); i++)
	{
		if (playerData.Name == this->game->players[i])
			this->playernumber = i + 1;
	}
	// auf gamemaster testen
	std::string playernames[4];
	int count = 0;
	while (this->game->players.size() >  count)
	{
		playernames[count] = this->game->players[count];
		count++;
	}
	while (count < 4)
	{
		playernames[count] = "";
		count++;
	}

	this->players[0] = new Textblock(sf::Vector2f(10, 10),sf::Vector2f(100, 40), playernames[0], 30);
	m_DrawV.push_back(this->players[0]);
	this->players[1] = new Textblock(sf::Vector2f(10,50),sf::Vector2f(100, 40), playernames[1], 30);
	m_DrawV.push_back(this->players[1]);
	this->players[2] = new Textblock(sf::Vector2f(10,100),sf::Vector2f(100, 40), playernames[2], 30);
	m_DrawV.push_back(this->players[2]);
	this->players[3] = new Textblock(sf::Vector2f(10,150),sf::Vector2f(10000, 40), playernames[3], 30);
	m_DrawV.push_back(this->players[3]);

	this->mapName = new Textblock(sf::Vector2f(10, 200), sf::Vector2f(50, 20), "mapname", 30);
	m_DrawV.push_back(mapName);

	if (amIGamemaster == true)
	{
		this->kickPlayer[0] = new StandardButton(sf::Vector2f(10, 250), sf::Vector2f(50, 25), "kick", KICKP1, false, false); 
		this->kickPlayer[1] = new StandardButton(sf::Vector2f(40, 250), sf::Vector2f(50, 25), "kick", KICKP2, false, false); 
		this->kickPlayer[2] = new StandardButton(sf::Vector2f(70, 250), sf::Vector2f(50, 25), "kick", KICKP3, false, false); 
	}

	this->leave = new StandardButton(sf::Vector2f(10, 280), sf::Vector2f(100, 50), "leave", LEAVE, false);
	this->startgame = new StandardButton(sf::Vector2f(50, 280), sf::Vector2f(100, 50), "start", START, false);
	if (!amIGamemaster)
		this->startgame->setIsEnabled(false);

	for (int i = 0; i < 3; i++)
	{
		m_DrawV.push_back(kickPlayer[i]);
		m_AnimateV.push_back(kickPlayer[i]);
		m_ClickV.push_back(kickPlayer[i]);
	}

	if (amIGamemaster == true)
	{
		this->kickPlayer[0]->Attach(this);
		this->kickPlayer[1]->Attach(this);
		this->kickPlayer[2]->Attach(this);
	}

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
	if (amIGamemaster == true)
	{
		delete this->kickPlayer[0];
		delete this->kickPlayer[1];
		delete this->kickPlayer[2];	
	}
	delete this->leave;
	delete this->startgame;
}


void GameLobbyView::onButtonClick(int id)
{
	switch(id)
	{
		case LEAVE:
			{
				this->game->disconnect();
				this->m_nextView = Views::LOBBY;
				break;
			}
		case START:
			{
				this->game->startGame();
				this->m_nextView = Views::INGAME;
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
	int space = (size.y / 100) * 10;

	if (space < 50)
		space = 50;

	this->players[0]->setPos(Vector2f(size.x / 2 - this->players[0]->getSize().x / 2, size.y / 2 - 2 * this->players[0]->getSize().y - 1.5 * space));
	this->players[1]->setPos(Vector2f(size.x / 2 - this->players[1]->getSize().x / 2, size.y / 2 - this->players[1]->getSize().y - 0.5 * space));	
	this->players[2]->setPos(Vector2f(size.x / 2 - this->players[2]->getSize().x / 2, size.y / 2 + 0.5 * space));
	this->players[3]->setPos(Vector2f(size.x / 2 - this->players[3]->getSize().x / 2, size.y / 2 + this->players[3]->getSize().y + 1.5 * space));
	
	if (amIGamemaster == true)
	{
		this->kickPlayer[0]->setPosition(Vector2f(size.x / 2 - this->kickPlayer[0]->getSize().x / 2, this->players[1]->getPosition().y + this->players[1]->getSize().y + space / 4));
		this->kickPlayer[1]->setPosition(Vector2f(size.x / 2 - this->kickPlayer[1]->getSize().x / 2, this->players[2]->getPosition().y + this->players[2]->getSize().y + space / 4));
		this->kickPlayer[2]->setPosition(Vector2f(size.x / 2 - this->kickPlayer[2]->getSize().x / 2, this->players[3]->getPosition().y + this->players[3]->getSize().y + space / 4));
	}

	this->leave->setPosition(size.x / 2 - this->players[3]->getSize().x, this->players[3]->getPosition().y + this->players[3]->getSize().y + space);

	this->startgame->setPosition(this->players[3]->getPosition().x + this->players[3]->getSize().x - this->startgame->getSize().x, this->players[3]->getPosition().y + this->players[3]->getSize().y + space);
}

