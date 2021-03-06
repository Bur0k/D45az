#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "IDrawable.h"
#include "IClickable.h"
#include "graphic_globals.h"
#include "IButtonfunction.h"
#include "IAnimatable.h"
#include "IView.h"
#include "StandardButton.h"
#include "Statusbar.h"
#include "Textblock.h"
#include "Slider.h"
#include "Map.h"
#include "Textbox.h"
#include "LoginView.h"
#include "LobbyView.h"
#include "GameLobbyView.h"
#include "MenuView.h"
#include "CommitButton.h"
#include "IngameView.h"

#include "MusikSampler.h"

using namespace sf;



//#define MOUSEGRAB

// TODO derive game from renderWindow
// manages gui views and timers
class Game : private IButtonfunction, private ISliderFunction, public ITextBoxFunction, public StatusBarFunctions
{
private:
	//debug
	Button* b;
	Button* b1;
	Button* b2;
	Button* b3;
	Button* b4;

	
	TextBox* tb;
	Textblock* tblock;
	MusikSampler* m_pMS;

	Slider* s;
	Slider* s1;

	Map map;
	int xMap,yMap;

	///end debug

	SpriteTex m_falseMouse;

	std::vector<IView*> m_ViewVect;
	IView* m_pCurrentView;
	Views m_ViewMode;

	Clock m_fpsCounter;
	Clock m_animationTimer;
	Clock m_audioCheck;

	RenderWindow* m_pWindow;
	
	Vector2f m_size;
	ClickVect m_clickL;
	DrawVect m_drawL;
	AnimateVect m_animateL;
	KeyInputVect m_keyInputL;


	bool m_inFocus;

	//The Menu should not be opened and closed while just holding down the esc key
	bool m_menubutton;

	Vector2i m_lastMousePosition;

	void ResetMouse();

public:
	Text m_fpsText;
	Game(RenderWindow* rw, Views Viewmode, Vector2f windowSize);
	~Game();
	//setter & getter
	void setMenubottun(bool onoff); // vilt überflüssig
	void OpenMenu(); // zu übergebende funtktion

	//draws the current screen
	void Draw();
	//manages the user input
	void Input();
	void timer();

	Views getView();
	void onClose();

	

public:

	void LoadView(Views);
	void onButtonClick(int);

	void DrawGame();
	void DrawMainMenu();
	void DrawLogin();
	void DrawLobby();
	void DrawIngameMenu();


	void DrawTest();

	void update();

	void LoadView();

	//interfaces

	void onMouseMove();
	void onResize();
	
	void onMouseDownLeft();
	void onMouseDownRight();
	void onMouseUpLeft();
	void onMouseUpRight();
	void onTextEntered(sf::Event e);
	void onKeyDown(sf::Event e);
	void onKeyUp(sf::Event e);

	void onSliderValueChange(int ID, double position);
	void onSliderReleased(int ID, double position);
	virtual void onTextBoxSend(int ID, std::string s);
	
};
#endif
