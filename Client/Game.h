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
#include "Textblock.h"
#include "Slider.h"

#include "MusikSampler.h"

using namespace sf;

//#define MOUSEGRAB

// TODO derive game from renderWindow

// manages gui views and timers
class Game : private IButtonfunction, private ISliderFunction
{
private:
	//debug

	Button* b;
	Button* b1;
	Button* b2;
	Button* b3;

	Textblock* tblock;

	MusikSampler* m_pMS;

	Slider* s;

	///end debug
	Clock m_fpsCounter;
	Clock m_animationTimer;
	RenderWindow* m_pWindow;
	ScreenMode m_Screen;
	Vector2f m_size;
	Font m_stdFont;
	ClickList m_clickL;
	DrawVect m_drawL;
	AnimateVect m_animateL;

	Text m_fpsText;

	bool m_inFocus;

	Vector2i m_lastMousePosition;


public:
	Game(RenderWindow* rw, ScreenMode sm, Vector2f windowSize);
	~Game();
	
	//draws the current screen
	void Draw();
	//manages the user input
	void Input();
	void timer();

	void setScreen(ScreenMode sm);
	ScreenMode getScreen();

private:
	void onButtonClick(int);

	void DrawGame();
	void DrawMainMenu();
	void DrawLogin();
	void DrawLobby();
	void DrawIngameMenu();


	void DrawTest();

	void Update();

	void onMouseMove();
	void onResize();
	void onMouseDownLeft();
	void onMouseDownRight();
	void onMouseUpLeft();
	void onMouseUpRight();
	void onMouseLeave();

	void onKeyDown(sf::Event e);
	void onKeyUp(sf::Event e);

	void onSliderValueChange(int ID, double position);
	void onSliderReleased(int ID, double position);
	
};

#endif
