#include "Game.h"

void foo(void)
{
	static int blubb = 0;
	blubb ++;
	std::cout << "button click accepted " << blubb << std::endl;
}


Game::Game(RenderWindow* rw, ScreenMode sm, Vector2f windowSize)
{
	m_pWindow = rw;
	m_Screen = sm;
	m_size = windowSize;

	//Lade font
	m_stdFont = sf::Font();
	if(!m_stdFont.loadFromFile("Data/Fonts/arial.ttf"))
		std::cout << "font load failed!" << std::endl;
	else
		std::cout << "font load successful!" << std::endl;

	m_animationTimer.restart();

	b = new Button(Vector2f(500,100),Vector2f(200,100),"hello world2");
	
	b->attachFunction(foo);
	clickL.push_back(b);
	
}

Game::~Game()
{
	delete b;
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

	b->draw(m_pWindow);
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

	for(unsigned int i = 0; i < clickL.size(); i++)
		clickL[i]->isHit(mousePos);
}

void Game::onMouseDownLeft()
{
	for(unsigned int i = 0; i < clickL.size(); i++)
		clickL[i]->PressedLeft();
}

void Game::onMouseDownRight()
{
	for(unsigned int i = 0; i < clickL.size(); i++)
		clickL[i]->PressedRight();
}

void Game::onMouseUpLeft()
{
	for(unsigned int i = 0; i < clickL.size(); i++)
		clickL[i]->ReleasedLeft();
}

void Game::onMouseUpRight()
{
	for(unsigned int i = 0; i < clickL.size(); i++)
		clickL[i]->ReleasedRight();
}

void Game::Input()
{
	// CHECK EVENTS //

	sf::Event event;
	//works through the event stack
	while (m_pWindow->pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			m_pWindow->close();
		
		//resize
		else if(event.type == sf::Event::Resized)
			onResize();
		
		//mouse move
		else if(event.type == sf::Event::MouseMoved)
			onMouseMove();

		//mouse down
		else if(event.type == sf::Event::MouseButtonPressed)
			if(event.mouseButton.button == sf::Mouse::Left)
				onMouseDownLeft();
			else
				onMouseDownRight();

		//mouse up
		else if(event.type == sf::Event::MouseButtonReleased)
			if(event.mouseButton.button == sf::Mouse::Left)
				onMouseUpLeft();
			else
				onMouseUpRight();

	}

	// CHECK KEYBOARD INPUT //

	//closes the window on escape
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_pWindow->close();


}

void Game::timer()
{
	if(m_animationTimer.getElapsedTime().asMilliseconds() > 1000 / 33)
	{
		m_animationTimer.restart();
		b->animationTick();
		//... code
	}
}

