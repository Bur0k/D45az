#include "Game.h"

void Game::onButtonClick(int index)
{
	static int blubb = 0;

	switch(index)
	{
	case 1:
		blubb ++;
		m_pMS->next_song();
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

void Game::onSliderValueChange(int ID, double position)
{
	std::cout << "Slider CHANGED ID: " << ID << " Value: " << position << std::endl;
}

void Game::onSliderReleased(int ID, double position)
{
	std::cout << "Slider RELEASED ID: " << ID << " Value: " << position << std::endl;
}

void Game::onTextBoxSend(int ID, std::string s)
{
	std::cout << "TEXTBOX ID " << ID << " text:   " << s << std::endl;
}

Game::Game(RenderWindow* rw, Views sm, Vector2f windowSize)
{


	m_pWindow = rw;
	m_ViewMode = sm;
	m_size = windowSize;

	m_inFocus = true;
	m_lastMousePosition = Mouse::getPosition(*m_pWindow);

	m_stdFont = MyFonts::getFont(GameFonts::ARIAL);

	m_animationTimer.restart();
	m_fpsCounter.restart();



	tblock = new Textblock(Vector2f(20, 30), Vector2f(100, 200), "Es ist �berragend es ist toll asdfas adfdsaf asdfsdfsa asdfas", 20, 5);
	m_drawL.push_back(tblock);


	b = new StandardButton(Vector2f(500,100),Vector2f(200,60),"hello",1,false);
	
	b->attachFunction((IButtonfunction*)this);
	
	b1 = new Button(Vector2f(500,200),Vector2f(100,200), "|| SOUND 1 || \n Basisklasse \n Button \n automatische \n gr�ssenanpassung", 2, false);

	b1->attachFunction((IButtonfunction*)this);

	b2 = new StandardButton(Vector2f(500,500), Vector2f(170,100),"Musik stoppen", 4, false);

	b2->attachFunction((IButtonfunction*)this);

	b3 = new StandardButton(Vector2f(300,600), Vector2f(120,100),"|| SOUND 2 || \n buttons k�nnen auch\nein und aus schalten" , 3, true);

	b3->attachFunction(this);

	s = new Slider(true, Vector2f(400,50), 0.5, Vector2f(30, 500), 1);
	
	s->Attach(this);

	s1 = new Slider(false, Vector2f(30,200), 0.4, Vector2f(700,200), 2);

	s1->Attach(this);

	tb = new TextBox(500, "das ist eine textbox", Vector2f(100,600), true, 1);

	tb->attach(this);


	m_fpsText.setFont(m_stdFont);
	m_fpsText.setPosition((float)m_pWindow->getSize().x - 50, 30);
	m_fpsText.setColor(MyColors.Red);


	m_clickL.push_back(b);
	m_clickL.push_back(b1);
	m_clickL.push_back(b2);
	m_clickL.push_back(b3);
	m_clickL.push_back(s);
	m_clickL.push_back(s1);
	m_clickL.push_back(tb);
	
	m_drawL.push_back(b);
	m_drawL.push_back(b1);
	m_drawL.push_back(b2);
	m_drawL.push_back(b3);
	m_drawL.push_back(s);
	m_drawL.push_back(s1);
	m_drawL.push_back(tb);

	m_animateL.push_back(b);
	m_animateL.push_back(b1);
	m_animateL.push_back(b2);
	m_animateL.push_back(b3);
	m_animateL.push_back(tb);

	m_keyInputL.push_back(tb);

	// Musik Test Zeug

	m_pMS = new MusikSampler();
	/*
	MS->load_music(0);
	MS->play_music();
	*/

	map.load("Data/Maps/test.tmx");
	xMap=yMap=0;
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
	delete s;
	delete s1;
	delete tb;

	delete tblock;

	delete m_pMS;
}

void Game::setView(Views sm)
{
	m_ViewMode = sm;
}

Views Game::getView()
{
	return m_ViewMode;
}

void Game::Draw()
{
	switch (m_ViewMode)
	{
	case INGAME:
		DrawGame();
		break;
	case LOGIN:
		DrawLogin();
		break;
	case MENUE:
		DrawMainMenu();
		break;
	case LOBBY:
		DrawLobby();
		break;
	case INGAME_MENU:
		DrawGame();
		DrawIngameMenu();
		break;
	case TESTSCREEN:
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
	sf::IntRect RenderRect(xMap,yMap,m_pWindow->getSize().x,m_pWindow->getSize().y);
	map.render(*m_pWindow, RenderRect);

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
	
	m_fpsText.setPosition((float)m_pWindow->getSize().x - 50, 30);

	//std::cout << "Changing View on Resize :  " << "x" << m_pWindow->getSize().x << " x " << m_pWindow->getSize().y << std::endl;
				
}

void Game::onMouseMove()
{
	Vector2i mousePos = Mouse::getPosition(*m_pWindow);
	Vector2i mpm = Mouse::getPosition();

	//std::cout << " Window Mouse Position  x " << mpm.x << " y " << mpm.y << std::endl;

	for(int i = (signed)m_clickL.size() - 1; i >= 0; i--)
		m_clickL[i]->isHit(mousePos);

	m_lastMousePosition = mousePos;
}

void Game::onMouseDownLeft()
{
	for(int i = (signed)m_clickL.size() - 1; i >= 0; i--)
		if(m_clickL[i]->PressedLeft())
			break;
}

void Game::onMouseDownRight()
{
	for(int i = (signed)m_clickL.size() - 1; i >= 0; i--)
		if(m_clickL[i]->PressedRight())
			break;
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
	for(int i = (signed)m_clickL.size() - 1; i >= 0; i--)
		if(m_clickL[i]->ReleasedLeft())
			break;
}

void Game::onMouseUpRight()
{
	for(int i = (signed)m_clickL.size() - 1; i >= 0; i--)
		if(m_clickL[i]->ReleasedRight())
			break;
}

void Game::onKeyDown(sf::Event e)
{
	for(unsigned int i = 0; i < m_keyInputL.size(); i++)
		m_keyInputL[i]->onKeyDown(e);
	
	if(e.key.code == Keyboard::F)
		b->move(-6,0);
	else if(e.key.code == Keyboard::Left)
		xMap-=5;
	else if(e.key.code == Keyboard::Right)
		xMap+=5;
	else if(e.key.code == Keyboard::Up)
		yMap-=5;
	else if(e.key.code == Keyboard::Down)
		yMap+=5;

	if(e.key.code == Keyboard::G)
		s->move(Vector2f(1,1));
}

void Game::onKeyUp(sf::Event e)
{
	for(unsigned int i = 0; i < m_keyInputL.size(); i++)
		m_keyInputL[i]->onKeyUp(e);

#ifdef _DEBUG
	if(e.key.code == sf::Keyboard::Escape) 
		m_pWindow->close();
#endif
}

void Game::onTextEntered(sf::Event e)
{
	Uint32 c = e.text.unicode;
	if((c >= 32 && c <= 126) || c == 0x00F6 || c == 0x00FC || c == 0x00E4 || c == 0x00C4 || c == 0x00D6	|| c == 0x00DC || c == 0x00DF || c == 0x0FD6 )
	{
		std::string s;
		s = c;
		for(unsigned int i = 0; i < m_keyInputL.size(); i++)
			m_keyInputL[i]->onTextInput(s);
	}
}


void Game::onClose()
{
	MyFonts::deleteFonts();
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

		case sf::Event::TextEntered:
			if(m_inFocus)
				onTextEntered(event);
			break;

		default:
			break;
		}
	}
}

void Game::timer()
{
	static int fpsCount = 0;
	static int animationtime = 0;
	
	//std::cout<<m_animationTimer.getElapsedTime().asMilliseconds()<<std::endl;
	

	//ANIMATION//
	animationtime += m_animationTimer.getElapsedTime().asMilliseconds();
	m_animationTimer.restart();
	while(animationtime > 1000 / 33)
	{
		animationtime -= 1000 / 33;
		for(unsigned int i = 0; i < m_animateL.size(); i++)
			m_animateL[i]->animationTick();
	}


	//...//
	if(m_fpsCounter.getElapsedTime().asSeconds() >= 1)
	{
		m_fpsCounter.restart();
		m_fpsText.setString(std::to_string(fpsCount));
		fpsCount = 0;
	}

	fpsCount++;
	//more timers ...
}
