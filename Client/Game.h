#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "IClickable.h"
#include "graphic_globals.h"

using namespace sf;

typedef std::vector<IClickable*> ClickList;

enum ScreenMode {Ingame, Login, Menue, Lobby, IngameMenu, Testscreen};


class Game 
{
private:
	//debug 

	Button* b;

	///endDebug
	Clock m_animationTimer;
	RenderWindow* m_pWindow;
	ScreenMode m_Screen;
	Vector2f m_size;
	Font m_stdFont;
	ClickList clickL;

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

	

private:
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
	
};

#endif
