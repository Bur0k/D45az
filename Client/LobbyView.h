#ifndef LOBBYVIEW_H
#define LOBBYVIEW_H

#include "IView.h"
#include "Textblock.h"
#include <vector>
#include "StandardButton.h"
#include "Slider.h"

class LobbyView : public IView , public IButtonfunction, public ISliderFunction
{
public:
	LobbyView();
	~LobbyView();

	Textblock playerName;
	Textblock mapName;
	Textblock gameLobbyMaster;
	StandardButton* connect;

	Slider* s;
	struct GameLobbyData
	{
	public:
		Textblock lobbyName;
		Textblock playerCount;
	};
	std::vector<GameLobbyData*> gameLobbys;



	//implementing a lot of interfaces
	Views nextState();
	void onTextBoxSend(int ID, std::string s);

	void onButtonClick(int);

	void draw(sf::RenderWindow* rw);

	bool MouseMooved(sf::Vector2i &);
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

	void onResize();
};


#endif //LOGINVIEW_H