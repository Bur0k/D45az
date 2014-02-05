#include "GameLobbyView.h"

GameLobbyView::GameLobbyView(Vector2u & screensize)
{
	this->game = new GameLobby();
	this->windowsize = screensize;

	m_DrawV.push_back(&bg);

	
	this->players[0] = new Text("", MyFonts::getFont(GameFonts::ARIAL), 35);
	this->players[1] = new Text("", MyFonts::getFont(GameFonts::ARIAL), 35);
	this->players[2] = new Text("", MyFonts::getFont(GameFonts::ARIAL), 35);
	this->players[3] = new Text("", MyFonts::getFont(GameFonts::ARIAL), 35);
	
	this->mapName = new Text("mapname", MyFonts::getFont(GameFonts::ARIAL), 35);
	//m_DrawV.push_back(mapName);
	for (int i = 0; i < 4; i++)
		this->players[i]->setColor(MyColors.White);

	this->mapName->setColor(MyColors.White);


	
	this->kickPlayer[0] = new StandardButton(sf::Vector2f(10, 250), sf::Vector2f(50, 25), "kick", KICKP1, false, false); 
	this->kickPlayer[1] = new StandardButton(sf::Vector2f(40, 250), sf::Vector2f(50, 25), "kick", KICKP2, false, false); 
	this->kickPlayer[2] = new StandardButton(sf::Vector2f(70, 250), sf::Vector2f(50, 25), "kick", KICKP3, false, false); 

	this->kickPlayer[0]->setIsEnabled(false);
	this->kickPlayer[0]->setIsEnabled(false);
	this->kickPlayer[0]->setIsEnabled(false);


	this->leave = new StandardButton(sf::Vector2f(10, 280), sf::Vector2f(100, 50), "leave", LEAVE, false);
	this->startgame = new StandardButton(sf::Vector2f(50, 280), sf::Vector2f(100, 50), "start", START, false);

	this->startgame->setIsEnabled(false);

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
	delete this->game;

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
			this->game->disconnect();
			this->m_nextView = Views::LOBBY;
			break;
		}
	case START:
		{
			this->game->startGame();
			break;
		}
	case KICKP1:
		{
			for (unsigned int i = 0; i < this->game->players.size(); i++)
			{
				if (this->game->players[i] == this->players[1]->getString())
				{
					this->game->players[i] = "";
					//muss vermutlich noch an den Server gesendet werden
					this->players[1]->setString("");
				}
			}
			break;
		}
	case KICKP2:
		{
			for (unsigned int i = 0; i < this->game->players.size(); i++)
			{
				if (this->game->players[i] == this->players[2]->getString())
				{
					this->game->players[i] = "";
					//muss vermutlich noch an den Server gesendet werden
					this->players[2]->setString("");
				}
			}
			break;
		}
	case KICKP3:
		{
			for (unsigned int i = 0; i < this->game->players.size(); i++)
			{
				if (this->game->players[i] == this->players[3]->getString())
				{
					this->game->players[i] = "";
					//muss vermutlich noch an den Server gesendet werden
					this->players[3]->setString("");
				}
			}
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

	rw->draw(*players[0]);
	rw->draw(*players[1]);
	rw->draw(*players[2]);
	rw->draw(*players[3]);
	rw->draw(*this->mapName);
}

Views GameLobbyView::nextState()
{
	return m_nextView;
}

void GameLobbyView::update(double elapsedMs)
{
	static double elapsed = 0;
	elapsed += elapsedMs;

	if(elapsed >= 250)
	{
		elapsed = 0;

		if(game->updated & 1)	//player update
		{
			game->updated &= ~1;

			for (unsigned int i = 0; i < this->game->players.size(); i++)
			{
				this->players[i]->setString(this->game->players[i]);
			}
			centering(windowsize);
		}
		if(game->updated & 2)	//playerlimit updated
		{
			game->updated &= ~2;
		}
		if(game->updated & 4)	// gamemaster update
		{
			game->updated &= ~4;
			amIGamemaster = playerData.Name == game->gameMaster;

			if (amIGamemaster == true)
			{
				this->kickPlayer[0]->setIsEnabled(true);
				this->kickPlayer[1]->setIsEnabled(true);
				this->kickPlayer[2]->setIsEnabled(true);
				this->startgame->setIsEnabled(true);
			}
		}
		if(game->updated & 8)	// ingame
		{
			game->updated &= ~8;
			this->m_nextView = Views::INGAME;
		}
	}
}

void GameLobbyView::onResize(Vector2u & size)
{
	this->windowsize = size;
	centering(size);
}

Views GameLobbyView::getType()
{
	return Views::GAMELOBBY;
}


void GameLobbyView::centering(Vector2u & size)
{
	int space = (size.y / 100) * 10;

	
	bg.onResize(size);

	if (space < 50)
		space = 50;


	Rect<float> r = players[0]->getLocalBounds();

	this->players[0]->setPosition(Vector2f((float)(size.x / 2 + 30),(float)(size.y / 2 - 2 * r.height - 1.5 * space)));
	this->players[1]->setPosition(Vector2f((float)(size.x / 2 + 30), (float)(size.y / 2 - r.height - 0.5 * space)));	
	this->players[2]->setPosition(Vector2f((float)(size.x / 2 + 30), (float)(size.y / 2 + 0.5 * space)));
	this->players[3]->setPosition(Vector2f((float)(size.x / 2 + 30), (float)(size.y / 2 + r.height + 1.5 * space)));

	this->kickPlayer[0]->setPosition(Vector2f((float)(size.x / 2 + 20), (float)(this->players[1]->getPosition().y + r.height + space / 4)));
	this->kickPlayer[1]->setPosition(Vector2f((float)(size.x / 2 + 20), (float)(this->players[2]->getPosition().y + r.height + space / 4)));
	this->kickPlayer[2]->setPosition(Vector2f((float)(size.x / 2 + 20), (float)(this->players[3]->getPosition().y + r.height + space / 4)));

	this->leave->setPosition((float)(size.x / 2 - 200), (float)(this->players[3]->getPosition().y + r.height + space));

	this->startgame->setPosition((float)(this->players[0]->getPosition().x + r.width - this->startgame->getSize().x), (float)(this->players[3]->getPosition().y + r.height + space));

	this->mapName->setPosition(Vector2f((float)(size.x / 2 - 200), (float)(this->players[3]->getPosition().y)));
}

