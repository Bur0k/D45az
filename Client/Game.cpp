#include "Game.h"

void Game::onButtonClick(int index)
{
	static int blubb = 0;

	switch(index)
	{
	case 1:
		blubb ++;
		m_pMS->play_music(0);
		std::cout << "button click accepted " << blubb << std::endl;
		break;
	case 2:
		m_pMS->play_sound(0);
		std::cout << "other button click" << std::endl;
		break;
	case 3:
		m_pMS->play_sound(1);
		std::cout << "this button locks in and out  current status" << b3->getIsPressed() << std::endl;
		break;
	default:
		std::cout << "!! undefined button click !!" << std::endl;
		m_pMS->pause();
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

	m_stdFont = MyFonts.Arial;

	m_animationTimer.restart();
	m_fpsCounter.restart();



	tblock = new Textblock(Vector2f(20, 30), Vector2f(100, 100), "asdlkdjngsöljfngsäklnsdggllkjf", 5);
	m_drawL.push_back(tblock);


	b = new StandardButton(Vector2f(500,100),Vector2f(200,60),"hello",1,false);
	
	b->attachFunction((IButtonfunction*)this);
	
	b1 = new Button(Vector2f(500,200),Vector2f(100,200), "|| SOUND 1 || \n Basisklasse \n Button \n automatische \n grössenanpassung", 2, false);

	b1->attachFunction((IButtonfunction*)this);

	b2 = new StandardButton(Vector2f(500,500), Vector2f(170,100),"Musik stoppen", 4, false);

	b2->attachFunction((IButtonfunction*)this);

	b3 = new StandardButton(Vector2f(300,600), Vector2f(120,100),"|| SOUND 2 || \n buttons können auch\nein und aus schalten" , 3, true);

	b3->attachFunction(this);

	s = new Slider(true, Vector2f(200,50), 0.5, Vector2f(30, 500), 1);
	

	m_fpsText.setFont(m_stdFont);
	m_fpsText.setPosition(m_pWindow->getSize().x - 50, 30);
	m_fpsText.setColor(MyColors.Red);


	m_clickL.push_back(b);
	m_clickL.push_back(b1);
	m_clickL.push_back(b2);
	m_clickL.push_back(b3);
	m_clickL.push_back(s);
	
	m_drawL.push_back(b);
	m_drawL.push_back(b1);
	m_drawL.push_back(b2);
	m_drawL.push_back(b3);
	m_drawL.push_back(s);
	
	m_animateL.push_back(b);
	m_animateL.push_back(b1);
	m_animateL.push_back(b2);
	m_animateL.push_back(b3);

	m_Screen = Testscreen;


	// Musik Test Zeug

	m_pMS = new MusikSampler();
	/*
	MS->load_music(0);
	MS->play_music();
	*/
}

Game::~Game()
{
	m_clickL.clear();
	m_drawL.clear();
	m_animateL.clear();

	delete b;
	delete b1;
	delete b2;
	delete b3;

	delete tblock;

	delete m_pMS;
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

	m_pWindow->draw(m_fpsText);
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
	/*sf::Text t = sf::Text();
	t.setString("Hallo Welt\nD45az finezt.");
	t.setPosition(sf::Vector2f(200,200));
	t.setFont(m_stdFont);
	t.setColor(sf::Color::White);

	sf::RectangleShape r = sf::RectangleShape();
	r.setPosition(sf::Vector2f(200,400));
	r.setSize(sf::Vector2f(250,250));
	r.setFillColor(sf::Color::Blue);*/

	//m_pWindow->draw(t);
	//m_pWindow->draw(r);

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
	
	m_fpsText.setPosition(m_pWindow->getSize().x - 50, 30);

	//std::cout << "Changing View on Resize :  " << "x" << m_pWindow->getSize().x << " x " << m_pWindow->getSize().y << std::endl;
				
}

void Game::onMouseMove()
{
	Vector2i mousePos = Mouse::getPosition(*m_pWindow);
	Vector2i mpm = Mouse::getPosition();

	//std::cout << " Window Mouse Position  x " << mpm.x << " y " << mpm.y << std::endl;

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

void Game::onMouseLeave()
{
#ifdef MOUSEGRAB
	//TODO	this mouse grab hack does work if the scaling would be disabled
	//		though it results in massive mouse jitterling along the edge of the window which is not acceptable
	std::cout << " Mouse Left the Window " << std::endl;
	Mouse::setPosition(m_lastMousePosition, *m_pWindow);
#endif //MOUSEGRAB
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
	if(e.key.code == Keyboard::F)
		b->move(-6,0);
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
			if (m_inFocus) 
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

		case sf::Event::MouseLeft:	//TODO doesn't work on scalable boarders
			//TODO mouse grab only when in game mode not in menues or lobby
			if (m_inFocus)
				onMouseLeave();
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
	static int fpsCount = 0;

	//std::cout<<m_animationTimer.getElapsedTime().asMilliseconds()<<std::endl;
	if(m_animationTimer.getElapsedTime().asMilliseconds() > 1000 / 33)
	{
		m_animationTimer.restart();
		for(unsigned int i = 0; i < m_animateL.size(); i++)
			m_animateL[i]->animationTick();
	}

	if(m_fpsCounter.getElapsedTime().asSeconds() >= 1)
	{
		m_fpsCounter.restart();
		m_fpsText.setString(std::to_string(fpsCount));
		fpsCount = 0;
	}

	fpsCount++;
	//more timers ...
}

