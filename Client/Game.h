#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


using namespace sf;

typedef 

enum ScreenMode {Ingame, Login, Menue, Lobby, IngameMenu, Testscreen};


class Game 
{
private:
	RenderWindow* m_pWindow;
	ScreenMode m_Screen;
	Vector2f m_size;
	Font m_stdFont;

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

	void resize();

private:
	void DrawGame();
	void DrawMainMenu();
	void DrawLogin();
	void DrawLobby();
	void DrawIngameMenu();

	void DrawTest();

	void Render();
	void Update();
	
};

#endif
