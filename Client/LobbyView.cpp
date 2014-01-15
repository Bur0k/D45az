#include "LobbyView.h"


LobbyView::LobbyView():
	playerName(sf::Vector2f(0,0),sf::Vector2f(300,100),"Name",50,0),
	mapName(sf::Vector2f(500,200),sf::Vector2f(300,100),"MapName",20,0),
	gameLobbyMaster(sf::Vector2f(500,300),sf::Vector2f(300,100),"GameLobbyMaster",20,0)
{
	playerName.setPosition(0,0);
	mapName.setPosition(500,200);
	gameLobbyMaster.setPosition(500,300);
	connect = new StandardButton(sf::Vector2f(500,400),sf::Vector2f(100,75),"Connect",0,false);
	s = new Slider(false,sf::Vector2f(20,400),0.0,sf::Vector2f(450,200),0);

	connect->attachFunction(this);
	s->Attach(this);

	playerName.setText("Name",sf::Vector2f(300,100));
	mapName.setText("Map Name",sf::Vector2f(300,100));
	gameLobbyMaster.setText("GameLobby Master",sf::Vector2f(300,100));


	lobby = new Lobby();
	lobby->askforLobbyData();
	lobby->askforLobbyData();
	lobby->createNewGameLobby();
	while(lobby->gameLobby==NULL)
		;
	lobby->askforLobbyData();
	lobby->gameLobby->maxPlayerChange(3);
}

LobbyView::~LobbyView()
{
	delete lobby;
	delete connect;
	delete s;
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
		delete it->second;
	gameLobbys.clear();
}

void LobbyView::draw(sf::RenderWindow* rw)
{
	playerName.draw(rw);
	mapName.draw(rw);
	gameLobbyMaster.draw(rw);
	connect->draw(rw);
	s->draw(rw);

	int y = 200;
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
	{
		it->second->lobbyName.setPosition(20,y);
		it->second->playerCount.setPosition(200,y);
		y+=50;
		it->second->lobbyName.draw(rw);
		it->second->lobbyName.draw(rw);
	}
}

void LobbyView::onButtonClick(int)
{
	//handle incoming clicks here
}

void LobbyView::onTextBoxSend(int ID, std::string s)
{
	//recieve shit from textboxes
}


bool LobbyView::MouseMooved(sf::Vector2i & v)
{
	s->MouseMooved(v);
	connect->MouseMooved(v);
	return false;
}

bool LobbyView::PressedRight()
{
	return false;
}

bool LobbyView::PressedLeft()
{
	s->PressedLeft();
	connect->PressedLeft();
	return false;
}

bool LobbyView::ReleasedRight()
{
	return false;
}

bool LobbyView::ReleasedLeft()
{
	s->ReleasedLeft();
	connect->ReleasedLeft();
	return false;
}
	
void LobbyView::animationTick()
{
	connect->animationTick();
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

Views LobbyView::nextState()
{
	return NOCHANGE;
}

void LobbyView::onSliderValueChange(int ID, double position)
{

}
void LobbyView::onSliderReleased(int ID, double position)
{

}

void LobbyView::onResize()
{

}

void LobbyView::update(double elpasedMs)
{
	static int elapsed=0;
	elapsed+=elpasedMs;
	if(elapsed>=100)
	{
		elapsed=0;
		if(lobby->updated)
		{
			lobby->updated = false;
			
			for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
				delete it->second;
			gameLobbys.clear();

			lobby->m.lock();

			for(auto it = lobby->gamesCreated.begin();it!=lobby->gamesCreated.end();it++)
			{
				short id = it->first;
				GameLobbyData* GLA = new GameLobbyData();
				GLA->lobbyName.setText("Gamelobby Name",sf::Vector2f(200,30));
				string asdasd=std::to_string(it->second.players.size()) + " / " + std::to_string(it->second.playerlimit);
				GLA->playerCount.setText(asdasd,sf::Vector2f(200,30));
				gameLobbys[id] = GLA;
			}

			lobby->m.unlock();
		}
	}
}