#include "LobbyView.h"

int LobbyView::GameLobbyData::nextID = 10;

LobbyView::LobbyView():
	playerName(sf::Vector2f(0,0),sf::Vector2f(500,100),"Name",40),
	gameLobbyMaster(sf::Vector2f(500,300),sf::Vector2f(300,100),"GameLobbyMaster:",20),
	gameLobbyMasterValue(sf::Vector2f(500,400),sf::Vector2f(300,100),"",20),
	newGameLobbyName(300,"New Gamelobbyname",sf::Vector2f(500,700),1,0)
{
	playerName.setPos(sf::Vector2f(0,0));
	gameLobbyMaster.setPos(sf::Vector2f(500,300));
	gameLobbyMasterValue.setPos(sf::Vector2f(800,300));
	connect = new StandardButton(sf::Vector2f(500,400),sf::Vector2f(100,75),"Connect",0,false);
	updateLobbys = new StandardButton(sf::Vector2f(500,500),sf::Vector2f(100,75),"Update",1,false);
	creatNewGamelobby = new StandardButton(sf::Vector2f(500,600),sf::Vector2f(100,75),"Create New\nGamelobby",2,false);
	s = new Slider(false,sf::Vector2f(20,400),0.0,sf::Vector2f(450,200),0);

	connect->Attach(this);
	updateLobbys->Attach(this);
	creatNewGamelobby->Attach(this);
	s->Attach(this);

	playerName.setText(playerData.Name,sf::Vector2f(500,100));
	gameLobbyMaster.setText("GameLobby Master",sf::Vector2f(300,100));


	newGameLobbyName.Attach(this);

	next = Views::NOCHANGE;

	lobby = new Lobby();
	lobby->askforLobbyData();
}

LobbyView::~LobbyView()
{
	delete lobby;
	delete connect;
	delete updateLobbys;
	delete creatNewGamelobby;

	delete s;
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
	{
		delete it->second->LE;
		delete it->second;
	}
	gameLobbys.clear();
}

void LobbyView::draw(sf::RenderWindow* rw)
{
	playerName.draw(rw);
	newGameLobbyName.draw(rw);
	gameLobbyMaster.draw(rw);
	gameLobbyMasterValue.draw(rw);
	connect->draw(rw);
	updateLobbys->draw(rw);
	creatNewGamelobby->draw(rw);

	s->draw(rw);

	int y = 200;
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
	{
		it->second->LE->setPosition(sf::Vector2f(20.0,y));
		it->second->LE->draw(rw);
		y+=50;
	}
}

void LobbyView::onButtonClick(int id)
{
		
	if(id == 0)
	{
		for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
			if(it->second->LE->getIsEnabled())
				lobby->connectToGameLobby(it->second->LE->getID()-10);
	}
	else if( id == 1)
	{
		lobby->askforLobbyData();
	}
	else if( id == 2)
	{
		lobby->createNewGameLobby(newGameLobbyName.getText());
	}
	else if(id > 10)
	{
		for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
		{
			if(it->second->LE->getID() != id && it->second->LE->getIsEnabled())
				it->second->LE->unLock();
			if(it->second->LE->getID() == id)
			{
				gameLobbyMasterValue.setText(lobby->gamesCreated[id-10].gameMaster.Name,sf::Vector2f(300,100));
				gameLobbyMasterValue.setBackgroundColor(MyColors.White);
			}
		}
	}
	//handle incoming clicks here
}


bool LobbyView::MouseMoved(sf::Vector2i & v)
{
	s->MouseMoved(v);
	connect->MouseMoved(v);
	updateLobbys->MouseMoved(v);
	creatNewGamelobby->MouseMoved(v);
	newGameLobbyName.MouseMoved(v);
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
		it->second->LE->MouseMoved(v);
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
	updateLobbys->PressedLeft();
	creatNewGamelobby->PressedLeft();
	newGameLobbyName.PressedLeft();
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
		it->second->LE->PressedLeft();
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
	updateLobbys->ReleasedLeft();
	creatNewGamelobby->ReleasedLeft();
	newGameLobbyName.ReleasedLeft();
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
		it->second->LE->ReleasedLeft();
	return false;
}
	
void LobbyView::animationTick()
{
	connect->animationTick();
	updateLobbys->animationTick();
	creatNewGamelobby->animationTick();
	newGameLobbyName.animationTick();
	for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
		it->second->LE->animationTick();
}
	
void LobbyView::onKeyDown(sf::Event e)
{
	newGameLobbyName.onKeyDown(e);
}

void LobbyView::onKeyUp(sf::Event e)
{
	newGameLobbyName.onKeyUp(e);
}

void LobbyView::onTextInput(std::string s)
{
	newGameLobbyName.onTextInput(s);
}

Views LobbyView::nextState()
{
	return next;
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

void LobbyView::pt1zyklisch(double elpasedMs)
{
	static double elapsed=0;
	elapsed+=elpasedMs;
	if(elapsed>=100)
	{
		elapsed=0;
		if(lobby->pt1zyklischd)
		{
			lobby->pt1zyklischd = false;
			
			for(auto it = gameLobbys.begin();it!=gameLobbys.end();it++)
			{
				delete it->second->LE;
				delete it->second;
			}
			gameLobbys.clear();

			lobby->m.lock();

			for(auto it = lobby->gamesCreated.begin();it!=lobby->gamesCreated.end();it++)
			{
				short id = it->first + 10;
				GameLobbyData* GLA = new GameLobbyData();

				GLA->LE = new LobbyEntry(sf::Vector2f(420,50),sf::Vector2f(),it->second.name,it->second.players.size(),it->second.playerlimit,id);
				GLA->LE->Attach(this);

				gameLobbys[id] = GLA;
			}
			lobby->m.unlock();
		}
	}
}

Views LobbyView::getType()
{
	return Views::LOBBY;
}

void LobbyView::onTextBoxSend(int ID, std::string s)
{
}