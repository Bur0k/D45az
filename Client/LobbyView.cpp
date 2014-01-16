#include "LobbyView.h"

int LobbyView::GameLobbyData::nextID = 0;

LobbyView::LobbyView():
	playerName(sf::Vector2f(0,0),sf::Vector2f(300,100),"Name",50),
	mapName(sf::Vector2f(500,200),sf::Vector2f(300,100),"MapName",20),
	gameLobbyMaster(sf::Vector2f(500,300),sf::Vector2f(300,100),"GameLobbyMaster",20)
{
	playerName.setPos(sf::Vector2f(0,0));
	mapName.setPos(sf::Vector2f(500,200));
	gameLobbyMaster.setPos(sf::Vector2f(500,300));
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
	lobby->createNewGameLobby("MeinefkingLobby");
	while(lobby->gameLobby.operator GameLobby *()==NULL)
		;
	lobby->askforLobbyData();
	lobby->gameLobby.operator GameLobby *()->maxPlayerChange(3);
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
		/*it->second->lobbyName.setPos(sf::Vector2f(20,y));
		it->second->playerCount.setPos(sf::Vector2f(400,y));
		y+=50;
		it->second->lobbyName.draw(rw);
		it->second->playerCount.draw(rw);*/

		it->second->LE.setPosition(sf::Vector2f(20.0,y));
		it->second->LE.draw(rw);
		y+=50;
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


bool LobbyView::MouseMoved(sf::Vector2i & v)
{
	s->MouseMoved(v);
	connect->MouseMoved(v);
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
		it->second->LE.MouseMoved(v);
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
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
		it->second->LE.PressedLeft();
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
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
		it->second->LE.ReleasedLeft();
	return false;
}
	
void LobbyView::animationTick()
{
	connect->animationTick();
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
		it->second->LE.animationTick();
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
	return Views::NOCHANGE;
}

void LobbyView::onSliderValueChange(int ID, double position)
{

}
void LobbyView::onSliderReleased(int ID, double position)
{

}

void LobbyView::onResize(Vector2u &)
{

}

void LobbyView::update(double elpasedMs)
{
	static double elapsed=0;
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

				GLA->LE.setName("Gamelobby Name");
				GLA->LE.setMaxPlayers(it->second.playerlimit);
				GLA->LE.setPlayers(it->second.players.size());
				
				GLA->lobbyName.setFontColor(sf::Color(255,255,255,255));
				GLA->lobbyName.setBackgroundColor(sf::Color(255,255,255,0));
				GLA->playerCount.setFontColor(sf::Color(255,255,255,255));
				GLA->playerCount.setBackgroundColor(sf::Color(255,255,255,0));

				gameLobbys[id] = GLA;
			}

			lobby->m.unlock();
		}
	}
}