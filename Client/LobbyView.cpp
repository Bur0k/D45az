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

void LobbyView::onButtonClick(int)
{
	//handle incoming clicks here
}

void LobbyView::onTextBoxSend(int ID, std::string s)
{
	//recieve shit from textboxes
}


bool LobbyView::isHit(sf::Vector2i &)
{
	
}

bool LobbyView::PressedRight()
{

}

bool LobbyView::PressedLeft()
{

}

bool LobbyView::ReleasedRight()
{

}

bool LobbyView::ReleasedLeft()
{

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

void LobbyView::draw(sf::RenderWindow* rw)
{

}