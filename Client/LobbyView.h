#ifndef LOBBYVIEW_H
#define LOBBYVIEW_H

#include "IView.h"
#include "Textblock.h"
#include <vector>
#include "StandardButton.h"
#include "Slider.h"
#include "Lobby.h"
#include "LobbyEntry.h"

class LobbyView : public IView , public IButtonfunction, public ISliderFunction
{
public:
	LobbyView();
	~LobbyView();

	Textblock playerName;
	Textblock mapName;
	Textblock gameLobbyMaster;
	StandardButton* updateLobbys;
	StandardButton* creatNewGamelobby;
	StandardButton* connect;

	Slider* s;
	class GameLobbyData
	{
	public:
		static int nextID;
		int id;
		LobbyEntry* LE;
		GameLobbyData()//:LE(sf::Vector2f(420,50),sf::Vector2f(),"",0,0,nextID)
		{id = nextID++;}
	};

	std::map<short,GameLobbyData*> gameLobbys;

	Lobby* lobby;

	//implementing a lot of interfaces
	Views nextState();

	void onButtonClick(int);

	void draw(sf::RenderWindow* rw);

	bool MouseMoved(sf::Vector2i &);
	bool PressedRight();
	bool PressedLeft();
	bool ReleasedRight();
	bool ReleasedLeft();
	
	void animationTick(); 
	
	void onKeyDown(sf::Event);
	void onKeyUp(sf::Event);
	void onTextInput(std::string s);

	void onSliderValueChange(int ID, double position);
	void onSliderReleased(int ID, double position);

	void onResize(sf::Vector2u &);

	void update(double elpasedMs);

	virtual Views getType();
};


#endif //LOGINVIEW_H