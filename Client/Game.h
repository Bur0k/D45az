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

using namespace sf;



// manages gui views and timers
class Game : private IButtonfunction
{
private:
	//debug

	Button* b;
	Button* b1;

	///endDebug
	Clock m_animationTimer;
	RenderWindow* m_pWindow;
	ScreenMode m_Screen;
	Vector2f m_size;
	Font m_stdFont;
	ClickList m_clickL;
	DrawVect m_drawL;
	AnimateVect m_animateL;

	bool m_inFocus;

	Vector2i m_lastMousePosition;


public:
	Game(RenderWindow* rw, ScreenMode sm, Vector2f windowSize);
	~Game();
	
	//draws the current screen
	void Draw();
	//displays drawn image in the window
	void Display();
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

	void onResize();

	void Render();
	void Update();

	void onMouseMove();

	void onMouseDownLeft();
	void onMouseDownRight();
	void onMouseUpLeft();
	void onMouseUpRight();
	void onKeyDown(sf::Event e);
	void onKeyUp(sf::Event e);
	
};

#endif
