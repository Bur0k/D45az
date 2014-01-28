#ifndef LOBBYVIEW_H
#define LOBBYVIEW_H

#include "IView.h"
#include "Textblock.h"
#include <vector>
#include "StandardButton.h"
#include "Slider.h"
#include "Lobby.h"
#include "LobbyEntry.h"
#include "Textbox.h"
#include "Background.h"

class LobbyView : public IView , public IButtonfunction, public ISliderFunction, public ITextBoxFunction
{
	Background bg;
	Views next;
	Textblock playerName;
	TextBox newGameLobbyName;
	Textblock gameLobbyMaster;
	Textblock gameLobbyMasterValue;
	StandardButton* updateLobbys;
	StandardButton* creatNewGamelobby;
	StandardButton* connect;
	Slider* s;
	class GameLobbyData
	{
	public:
		static int nextID;
		LobbyEntry* LE;
		GameLobbyData()//:LE(sf::Vector2f(420,50),sf::Vector2f(),"",0,0,nextID)
		{}
	};

	sf::Vector2f lobbyStartPos;
	sf::Vector2f currentSize;


	std::map<short,GameLobbyData*> gameLobbys;
	std::map<short,GameLobbyData*> toDisplay;

	Lobby* lobby;
	void updateDisplayedGameLobbys();
public:
	LobbyView(sf::Vector2u currentView);
	~LobbyView();



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

	void pt1zyklisch(double elapsedMs);

	virtual Views getType();

	void onTextBoxSend(int ID, std::string s);
};


#endif //LOGINVIEW_H