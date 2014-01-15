#include "LobbyView.h"


LobbyView::LobbyView()
{
	playerName.setPosition(0,0);
	mapName.setPosition(500,200);
	gameLobbyMaster.setPosition(500,300);
	connect = new StandardButton(sf::Vector2f(500,400),sf::Vector2f(100,75),"Connect",0,false);
	s = new Slider(false,sf::Vector2f(50,400),0.0,sf::Vector2f(450,200),0);

	connect->attachFunction(this);
	s->Attach(this);
}

LobbyView::~LobbyView()
{
	delete connect;
	delete s;
}

void LobbyView::draw(sf::RenderWindow* rw)
{
	for(unsigned int i=0;i<gameLobbys.size();i++)
	{
		gameLobbys[i]->lobbyName.draw(rw);
		gameLobbys[i]->playerCount.draw(rw);
	}
	playerName.draw(rw);
	mapName.draw(rw);
	gameLobbyMaster.draw(rw);
	connect->draw(rw);
	s->draw(rw);
}

void LobbyView::onButtonClick(int)
{
	//handle incoming clicks here
}

void LobbyView::onTextBoxSend(int ID, std::string s)
{
	//recieve shit from textboxes
}


bool LobbyView::MouseMooved(sf::Vector2i &)
{
	return true;
}

bool LobbyView::PressedRight()
{
	return true;
}

bool LobbyView::PressedLeft()
{
	return true;
}

bool LobbyView::ReleasedRight()
{
	return true;
}

bool LobbyView::ReleasedLeft()
{
	return true;
}
	
void LobbyView::animationTick()
{

}
	
void LobbyView::onKeyDown(sf::Event)
{

}

void LobbyView::onKeyUp(sf::Event)
{

}

void LobbyView::onTextInput(std::string s)
{

}