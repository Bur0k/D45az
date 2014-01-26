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
		m_pMS->play_sound(0);
		std::cout << "other button click" << std::endl;
		break;
	case 3:
		m_pMS->play_sound(1);
		std::cout << "this button locks in and out  current status" << b3->getIsPressed() << std::endl;
		break;
	default:
		std::cout << "!! undefined button click !!" << std::endl;
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

Game::Game(RenderWindow* rw, Views Viewmode, Vector2f windowSize)
{
	m_pWindow = rw;
	m_ViewMode = Viewmode;
	m_size = windowSize;

	m_inFocus = true;
	m_menubutton = false;


	ResetMouse();
	m_lastMousePosition = Mouse::getPosition(*m_pWindow);


	Image mouse;
	if(!mouse.loadFromFile("Data/Images/mouse.png"))
		std::cout << "game.cpp can't load image Data/Images/mouse.png" << std::endl;
	m_falseMouse.t.loadFromImage(mouse);
	m_falseMouse.s.setTexture(& m_falseMouse.t);
	m_falseMouse.s.setPosition(m_lastMousePosition.x, m_lastMousePosition.y);
	m_falseMouse.s.setSize(Vector2f(35,35));

	//timers
	m_animationTimer.restart();
	m_fpsCounter.restart();

	LoadView(Viewmode);

	//TESTSCREEN stuff
	tblock = new Textblock(Vector2f(20, 80), Vector2f(100, 100), "", 25);
	m_drawL.push_back(tblock);

	b = new StandardButton(Vector2f(500,100),Vector2f(200,60),"hello",1,false);
	
	b->Attach((IButtonfunction*)this);
	
	b1 = new Button(Vector2f(500,200),Vector2f(100,200), "|| SOUND 1 || \n Basisklasse \n Button \n automatische \n grössenanpassung", 2, false);

	b1->Attach((IButtonfunction*)this);

	b2 = new StandardButton(Vector2f(500,500), Vector2f(170,100),"Musik stoppen", 4, false);

	b2->Attach((IButtonfunction*)this);

	b3 = new StandardButton(Vector2f(300,600), Vector2f(120,100),"|| SOUND 2 || \n buttons können auch\nein und aus schalten" , 3, true);

	b3->Attach(this);
	
	b4 = new CommitButton(Vector2f(m_pWindow->getSize().x - 100, m_pWindow->getSize().y - 100 - 100),Vector2f(100,100),"mybutton",5,false, m_pWindow->getSize(), 20);
	b4->Attach((IButtonfunction*)this);

	s = new Slider(true, Vector2f(400,50), 0.5, Vector2f(30, 500), 1);
	
	s->Attach(this);

	s1 = new Slider(false, Vector2f(30,200), 0.4, Vector2f(700,200), 2);

	s1->Attach(this);

	tb = new TextBox(500, "das ist eine textbox", Vector2f(100,600), true, 1);

	tb->Attach(this);



	//FPS anzeige
	m_fpsText.setFont(MyFonts::getFont(GameFonts::ARIAL));
	m_fpsText.setPosition((float)m_pWindow->getSize().x - 150, 30);
	m_fpsText.setColor(MyColors.Red);


	m_clickL.push_back(b);
	m_clickL.push_back(b1);
	m_clickL.push_back(b2);
	m_clickL.push_back(b3);
	m_clickL.push_back(b4);
	m_clickL.push_back(s);
	m_clickL.push_back(s1);
	m_clickL.push_back(tb);
	
	m_drawL.push_back(b);
	m_drawL.push_back(b1);
	m_drawL.push_back(b2);
	m_drawL.push_back(b3);
	m_drawL.push_back(b4);
	m_drawL.push_back(s);
	m_drawL.push_back(s1);
	m_drawL.push_back(tb);

	m_animateL.push_back(b);
	m_animateL.push_back(b1);
	m_animateL.push_back(b2);
	m_animateL.push_back(b3);
	m_animateL.push_back(b4);
	m_animateL.push_back(tb);

	m_keyInputL.push_back(tb);


	//Musik
	m_pMS = new MusikSampler();
	m_pMS->next_song();

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
	delete b4;
	delete s;
	delete s1;
	delete tb;

	delete tblock;

	delete m_pMS;

	for(unsigned int i = 0; i < m_ViewVect.size(); i++)
		delete m_ViewVect[i];

	MyFonts::deleteFonts();

}

void Game::setMenubottun(bool onoff)
{
	m_menubutton = onoff;
}

Views Game::getView()
{
	return m_ViewMode;
}

void Game::Draw()
{
	if(m_ViewMode == Views::TESTSCREEN)
		DrawTest();
	else
		for(unsigned int i = 0; i < m_ViewVect.size(); i++)
			m_ViewVect[i]->draw(m_pWindow);

	//DrawMouse
	m_pWindow->draw(m_falseMouse.s);
	//ALLWAYS draw fps counter while in debug mode
//#ifdef _DEBUG
	m_pWindow->draw(m_fpsText);
//#endif
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
	m_size = (Vector2f)m_pWindow->getSize();
	m_pWindow->setSize(sf::Vector2u(m_pWindow->getSize().x, m_pWindow->getSize().y));
	v.setSize(sf::Vector2f((float)m_pWindow->getSize().x , (float)m_pWindow->getSize().y));
	v.setCenter(sf::Vector2f((float)m_pWindow->getSize().x / 2 , (float)m_pWindow->getSize().y / 2));
	m_pWindow->setView(v);

	//SBar->Resize(Vector2f(m_size.x, Statusbarheight)); // Statusbar anpassen

	((CommitButton*)b4)->onResize(m_pWindow->getSize());

	m_fpsText.setPosition((float)m_pWindow->getSize().x - 150, 30);

	if(m_ViewVect.size() > 0)
		m_ViewVect[m_ViewVect.size() - 1]->onResize(m_pWindow->getSize());
}

void Game::onMouseMove()
{
	Vector2u winSize = m_pWindow->getSize();
		
	Vector2i mousePos = Mouse::getPosition(*m_pWindow);
	if(mousePos.x == winSize.x / 2 && mousePos.y == winSize.y / 2)
	{
		m_lastMousePosition = mousePos;
		return; //return if mouse was resetted to the center of the screen
	}

	Vector2f delta = Vector2f(mousePos.x - m_lastMousePosition.x , mousePos.y - m_lastMousePosition.y);
	m_falseMouse.s.move(delta); //move displayed mouse

	m_lastMousePosition = mousePos;

	Vector2f mPos = m_falseMouse.s.getPosition();
	
	bool borderColisionX = false;
	bool xp = false;
	bool borderColisionY = false;
	bool yp = false;

	

	if(mPos.x > (float)winSize.x)
	{
		borderColisionX = true;
		xp = true;
	}
	else if(mPos.x < 0)
	{
		borderColisionX = true;
	}
	if(mPos.y > (float)winSize.y)
	{
		borderColisionY = true;
		yp = true;
	}
	else if(mPos.y < 0)
	{
		borderColisionY = true;
	}



	if(borderColisionX)
		m_falseMouse.s.setPosition((xp)? m_pWindow->getSize().x : 0, m_falseMouse.s.getPosition().y);
	
	if(borderColisionY)
		m_falseMouse.s.setPosition(m_falseMouse.s.getPosition().x, (yp)? m_pWindow->getSize().y : 0 );

	ResetMouse();

	
	//TODO alle mouse move aufrufe zu float umwandeln

	if(m_ViewMode == Views::TESTSCREEN)
	{
		//SBar->MouseMoved(mousePos); // Maus auf Statusbar?
		for(int i = (signed)m_clickL.size() - 1; i >= 0; i--)
			m_clickL[i]->MouseMoved((Vector2i)m_falseMouse.s.getPosition());
	}

	if(m_ViewMode == Views::INGAME)
	{
		int x = (borderColisionX)? (xp)? 1 : -1 : 0;
		int y = (borderColisionY)? (yp)? 1 : -1 : 0;
		static_cast<IngameView*>(m_ViewVect[m_ViewVect.size() - 1])->setScrollDirection(x,y);
	}


	m_lastMousePosition = mousePos;

	if(m_ViewVect.size() > 0)
		m_ViewVect[m_ViewVect.size() - 1]->MouseMoved((Vector2i)m_falseMouse.s.getPosition());
	
}

void Game::onMouseDownLeft()
{
	if(m_ViewMode == Views::TESTSCREEN)
	{
		for(int i = (signed)m_clickL.size() - 1; i >= 0; i--)
			if(m_clickL[i]->PressedLeft())
				break;	
	}

	if(m_ViewVect.size() > 0)
		m_ViewVect[m_ViewVect.size() - 1]->PressedLeft();
}

void Game::onMouseDownRight()
{
	if(m_ViewMode == Views::TESTSCREEN)
		for(int i = (signed)m_clickL.size() - 1; i >= 0; i--)
			if(m_clickL[i]->PressedRight())
				break;

	if(m_ViewVect.size() > 0)
		m_ViewVect[m_ViewVect.size() - 1]->PressedRight();
}


void Game::onMouseUpLeft()
{
	if(m_ViewMode == Views::TESTSCREEN)
		for(int i = (signed)m_clickL.size() - 1; i >= 0; i--)
			if(m_clickL[i]->ReleasedLeft())
				break;

	if(m_ViewVect.size() > 0)
		m_ViewVect[m_ViewVect.size() - 1]->ReleasedLeft();
}

void Game::onMouseUpRight()
{
	if(m_ViewMode == Views::TESTSCREEN)
	for(int i = (signed)m_clickL.size() - 1; i >= 0; i--)
		if(m_clickL[i]->ReleasedRight())
			break;

	if(m_ViewVect.size() > 0)
		m_ViewVect[m_ViewVect.size() - 1]->ReleasedRight();
}

void Game::onKeyDown(sf::Event e)
{
	if(m_ViewMode == Views::TESTSCREEN)
	for(unsigned int i = 0; i < m_keyInputL.size(); i++)
		m_keyInputL[i]->onKeyDown(e);
	
	if(m_ViewVect.size() > 0)
		m_ViewVect[m_ViewVect.size() - 1]->onKeyDown(e);
	
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
	if(e.key.code == Keyboard::Q)
		b3->unLock();
 	if(e.key.code == Keyboard::Escape && !m_menubutton)
		OpenMenu();
}

void Game::OpenMenu()
{
	this->LoadView(Views::MENU);
	m_menubutton = true;
}

void Game::onKeyUp(sf::Event e)
{
	for(unsigned int i = 0; i < m_keyInputL.size(); i++)
		m_keyInputL[i]->onKeyUp(e);

	if(m_ViewVect.size() > 0)
		m_ViewVect[m_ViewVect.size() - 1]->onKeyUp(e);

	if(e.key.code == Keyboard::Escape)
		m_menubutton = false;
}

void Game::onTextEntered(sf::Event e)
{
	Uint32 c = e.text.unicode;
	//filter input to all allowed characters
	if((c >= 32 && c <= 126) || c == 0x00F6 || c == 0x00FC || c == 0x00E4 || c == 0x00C4 || c == 0x00D6	|| c == 0x00DC || c == 0x00DF || c == 0x0FD6 )
	{
		std::string s;
		s = c;
		for(unsigned int i = 0; i < m_keyInputL.size(); i++)
			m_keyInputL[i]->onTextInput(s);

		if(m_ViewVect.size() > 0)
		m_ViewVect[m_ViewVect.size() - 1]->onTextInput(s);
	}
}

void Game::ResetMouse()
{
	Mouse::setPosition(Vector2i(m_pWindow->getSize().x / 2, m_pWindow->getSize().y / 2), *m_pWindow);
	m_lastMousePosition = Mouse::getPosition();
}

void Game::LoadView(Views v)
{

	//unfinished implementation
	bool clear = false;

	IView* NewView;

	switch (v)
	{
	case Views::NOCHANGE:
		return;
		break;
		
	case Views::GAMELOBBY:
		NewView = new GameLobbyView(m_pWindow->getSize());
		clear = true;
		break;

	case Views::INGAME:
		NewView = new IngameView(m_pWindow->getSize(), this, InagameViewPhases::WAITFORPLAYERS);
		clear = true;
		break;

	case Views::LOGIN:
		NewView = new LoginView(m_pWindow->getSize());
		clear = true;
		break;

	case Views::MENU:
		if(m_ViewMode == Views::MENU)
		{
			delete m_ViewVect[m_ViewVect.size() -1 ];
			m_ViewVect.pop_back();
			m_ViewMode = m_ViewVect[m_ViewVect.size() -1]->getType();
			return;
		}
		else 
		{
			m_ViewMode = v;
			NewView = new MenuView(m_pWindow->getSize(),false, m_pMS);
		}
		break;

	case Views::LOBBY:
		NewView = new LobbyView();
		clear = true;
		break;

	case Views::TESTSCREEN:
		return;
		break;

	case Views::CLOSE:
		m_pWindow->close();
		return;
		break;

	default:
		break;
	}

	if(clear)
	{
		for(unsigned int i = 0; i < m_ViewVect.size(); i++)
			delete m_ViewVect[i];
		m_ViewVect.clear();
	}

	m_ViewVect.push_back(NewView);
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
			m_pWindow->setMouseCursorVisible(false);
			ResetMouse();
			break;

		case sf::Event::LostFocus:
			m_inFocus = false;
			m_pWindow->setMouseCursorVisible(true);
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

	//check view for nextstate
	if(m_ViewVect.size() > 0 && m_ViewMode != Views::TESTSCREEN)
		LoadView(m_ViewVect[m_ViewVect.size() - 1]->nextState());
}

void Game::timer()
{
	static int fpsCount = 0;
	static int animationtime = 0;
	

	
	int elapsedMicro = m_animationTimer.getElapsedTime().asMicroseconds();
	m_animationTimer.restart();
	if(elapsedMicro < 10000)//Render und Hauptthread pausieren, damit der Prozessor entlastet wird. Aber nur wenn das spiel schnell genug läuft
		sleep(sf::milliseconds(1));

	animationtime += elapsedMicro;


	for(unsigned int i = 0;i<m_ViewVect.size();i++)
		m_ViewVect[i]->pt1zyklisch(static_cast<double>(elapsedMicro)/1000.0);
	
	
	//ANIMATION//
	while(animationtime > 1000000 / 33)//Animationtick 33 Hz
	{
		animationtime -= 1000000 / 33;
		if(m_ViewMode == Views::TESTSCREEN)
			for(unsigned int i = 0; i < m_animateL.size(); i++)
				m_animateL[i]->animationTick();

		for(unsigned int i = 0; i < m_ViewVect.size(); i++)
			m_ViewVect[i]->animationTick();
	}


	//frames per second Counter//
	fpsCount++;
	if(m_fpsCounter.getElapsedTime().asMilliseconds() >= 1000)
	{
		m_fpsCounter.restart();
		m_fpsText.setString(std::to_string(fpsCount));
		fpsCount = 0;
	}

	//more timers ...
}
