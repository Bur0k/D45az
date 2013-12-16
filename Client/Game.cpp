#include "Game.h"

Game::Game()
{
	
}

Game::~Game()
{

}

void Game::Draw()
{
	switch (m_Screen)
	{
	case Ingame:
		DrawGame();
		break;
	case Login:
		DrawLogin();
		break;
	case Menue:
		DrawMainMenu();
		break;
	case Lobby:
		DrawLobby();
		break;
	case IngameMenu:
		DrawGame();
		DrawIngameMenu();
		break;
	default:
		break;
	}
}

void Game::Input()
{

}

void Game::timer()
{

}