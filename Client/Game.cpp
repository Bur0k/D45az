#include "Game.h"

void Game::onButtonClick(int index)
{
	static int blubb = 0;
	switch(index)
	{
	case 1:
		
		blubb ++;
		std::cout << "button click accepted " << blubb << std::endl;
		break;
	case 2:
		std::cout << "other button click :)" << std::endl;
		break;
	default:
		std::cout << "undefined button click :(" << std::endl;
		break;
	}
}

Game::Game(RenderWindow* rw, ScreenMode sm, Vector2f windowSize)
{
	m_pWindow = rw;
	m_Screen = sm;
	m_size = windowSize;

	m_inFocus = true;
	m_lastMousePosition = Mouse::getPosition(*m_pWindow);

	//Lade font
	m_stdFont = MyFonts.Arial;

	m_animationTimer.restart();

	b = new Button(Vector2f(500,100),Vector2f(200,60),"hello",1);
	
	b->attachFunction((IButtonfunction*)this);
	
	b1 = new Button(Vector2f(500,200),Vector2f(100,200), "FU", 2);

	b1->attachFunction((IButtonfunction*)this);

	m_clickL.push_back(b);
	m_clickL.push_back(b1);
	m_drawL.push_back(b);
	m_drawL.push_back(b1);
	m_animateL.push_back(b);
	m_animateL.push_back(b1);

	m_Screen = Testscreen;

}

Game::~Game()
{
	delete b;
	delete b1;
}

void Game::setScreen(ScreenMode sm)
{
	m_Screen = sm;
}

ScreenMode Game::getScreen()
{
	return m_Screen;
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

	m_pWindow->draw(t);
	m_pWindow->draw(r);

	for(unsigned int i = 0; i < m_drawL.size(); i++)
		m_drawL[i]->draw(m_pWindow);
}

void Game::onResize()
{
	View v = m_pWindow->getView();
	m_pWindow->setSize(sf::Vector2u(m_pWindow->getSize().x, m_pWindow->getSize().y));
	v.setSize(sf::Vector2f((float)m_pWindow->getSize().x , (float)m_pWindow->getSize().y));
	v.setCenter(sf::Vector2f((float)m_pWindow->getSize().x / 2 , (float)m_pWindow->getSize().y / 2));
	m_pWindow->setView(v);
	
	//std::cout << "Changing View on Resize :  " << "x" << m_pWindow->getSize().x << " x " << m_pWindow->getSize().y << std::endl;
				
}

void Game::onMouseMove()
{
	Vector2i mousePos = Mouse::getPosition(*m_pWindow);

	///TODO Mouse grab

	for(unsigned int i = 0; i < m_clickL.size(); i++)
		m_clickL[i]->isHit(mousePos);

	m_lastMousePosition = mousePos;
}

void Game::onMouseDownLeft()
{
	for(unsigned int i = 0; i < m_clickL.size(); i++)
		m_clickL[i]->PressedLeft();
}

void Game::onMouseDownRight()
{
	for(unsigned int i = 0; i < m_clickL.size(); i++)
		m_clickL[i]->PressedRight();
}

void Game::onMouseUpLeft()
{
	for(unsigned int i = 0; i < m_clickL.size(); i++)
		m_clickL[i]->ReleasedLeft();
}

void Game::onMouseUpRight()
{
	for(unsigned int i = 0; i < m_clickL.size(); i++)
		m_clickL[i]->ReleasedRight();
}

void Game::onKeyDown(sf::Event e)
{

}

void Game::onKeyUp(sf::Event e)
{
#ifdef _DEBUG
	if(e.key.code == sf::Keyboard::Escape) 
		m_pWindow->close();
#endif
}

void Game::Input()
{
	//CHECK EVENTS//
	sf::Event event;

	//works through the event stack	
	while (m_pWindow->pollEvent(event))
	{
		switch (event.type)
		{
			/////WINDOW EVENTS/////
		case sf::Event::Closed:
			m_pWindow->close();
			break;

		case sf::Event::GainedFocus:
			m_inFocus = true;
			break;

		case sf::Event::LostFocus:
			m_inFocus = false;
			break;

		case sf::Event::Resized:
			onResize();
			break;

			/////MOUSE EVENTS/////
		case sf::Event::MouseMoved:
			onMouseMove();
			break;

		case sf::Event::MouseButtonPressed:
			if(event.mouseButton.button == sf::Mouse::Left && m_inFocus)
				onMouseDownLeft();
			else if (m_inFocus)
				onMouseDownRight();
			break;

		case sf::Event::MouseButtonReleased:
			if(event.mouseButton.button == sf::Mouse::Left && m_inFocus)
				onMouseUpLeft();
			else if (m_inFocus)
				onMouseUpRight();
			break;

			/////KEYBOARD EVENTS/////
		case sf::Event::KeyPressed:
			if(m_inFocus)
				onKeyDown(event);
			break;

		case sf::Event::KeyReleased:
			if(m_inFocus)
				onKeyUp(event);
			break;

		default:
			break;
		}
	}
}

void Game::timer()
{
	if(m_animationTimer.getElapsedTime().asMilliseconds() > 1000 / 33)
	{
		m_animationTimer.restart();
		for(unsigned int i = 0; i < m_animateL.size(); i++)
			m_animateL[i]->animationTick();
	}

	//more timers ...
}

