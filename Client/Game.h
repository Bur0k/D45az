#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

enum ScreenMode {Ingame, Login, Menue, Lobby, IngameMenu };

class Game 
{
private:
	sf::RenderWindow m_RW;
	ScreenMode m_Screen;

public:
	Game();
	~Game();
	
	//draws the current screen
	void Draw();
	//manages the user input
	void Input();
	void timer();


private:
	void DrawGame();
	void DrawMainMenu();
	void DrawLogin();
	void DrawLobby();
	void DrawIngameMenu();

	void Render();
	void Update();
	
};

#endif
