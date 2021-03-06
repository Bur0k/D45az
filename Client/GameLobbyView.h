#ifndef GAMELOBBYVIEW_H
#define GAMELOBBYVIEW_H

#include <vector>
#include <SFML\Graphics.hpp>
#include "IView.h"
#include "StandardButton.h"
#include "Slider.h"
#include "Textblock.h"
#include "Textbox.h"
#include "Unit.h"
#include "Map.h"
#include "GameLobby.h"
#include "PlayerData.h"
#include "Background.h"

extern PlayerData playerData;

class GameLobbyView : 
	public IView, public IButtonfunction, public ISliderFunction, public ITextBoxFunction
{
private:

	GameLobby* game;
	bool amIGamemaster;
	Background bg;
	Vector2u windowsize;
	enum click	{LEAVE, START, KICKP1, KICKP2, KICKP3};

	DrawVect m_DrawV;
	AnimateVect m_AnimateV;
	ClickVect m_ClickV;
	KeyInputVect m_KeyV;

	Views m_nextView;

	void centering(Vector2u & size);

public:
	GameLobbyView(Vector2u & screensize);
	~GameLobbyView();

	//Textblock* players[4];
	Text* players[4];
	Text* mapName;

	//Textblock* mapName;

	StandardButton* kickPlayer[3];
	StandardButton* leave;
	StandardButton* startgame;
	

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

	void onResize(sf::Vector2u &);
	void update(double elapsedMs);

	Views getType();

	Views nextState();

	void onButtonClick(int);
	void onSliderValueChange(int ID, double position);
	void onSliderReleased(int ID, double position);
	void onTextBoxSend(int ID, std::string s);
};





#endif //GAMELOBBYVIEW_H