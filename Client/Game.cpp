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

void Game::DrawGame()
{

}

void Game::DrawLogin()
{

}

void Game::DrawMainMenu()
{

}

void Game::DrawLobby()
{

}

void Game::DrawIngameMenu()
{

}



void Game::Input()
{

}

void Game::timer()
{

}