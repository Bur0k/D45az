#include "Game.h"

Game::Game(RenderWindow* rw, ScreenMode sm, Vector2f windowSize)
{
	m_RW = rw;
	m_Screen = sm;
	m_size = windowSize;

	//Lade font
	m_stdFont = sf::Font();
	if(!m_stdFont.loadFromFile("Data/Fonts/arial.ttf"))
		std::cout << "font load failed!" << std::endl;
	else
		std::cout << "font load successful!" << std::endl;
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
	case Testscreen:
		DrawTest();
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

void Game::DrawTest()
{
	sf::Text t = sf::Text();
	t.setString("Hallo Welt\nD45az finezt.");
	t.setPosition(sf::Vector2f(200,200));
	t.setFont(m_stdFont);
	t.setColor(sf::Color::White);

	sf::RectangleShape r = sf::RectangleShape();
	r.setPosition(sf::Vector2f(200,400));
	r.setSize(sf::Vector2f(250,250));
	r.setFillColor(sf::Color::Blue);

	m_RW->draw(t);
	m_RW->draw(r);
}

void Game::resize()
{
	View v = m_RW->getView();
	m_RW->setSize(sf::Vector2u(m_RW->getSize().x, m_RW->getSize().y));
	v.setSize(sf::Vector2f(m_RW->getSize().x , m_RW->getSize().y));
	v.setCenter(sf::Vector2f(m_RW->getSize().x / 2 , m_RW->getSize().y / 2));
	m_RW->setView(v);
	std::cout << "Changing View on Resize :  " << "x" << m_RW->getSize().x << " x " << m_RW->getSize().y << std::endl;
				
}

void Game::Input()
{

}

void Game::timer()
{

}