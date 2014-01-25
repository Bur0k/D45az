#include "MenuView.h"


MenuView::MenuView(Vector2u & screensize, bool extended, MusikSampler* MS)
{
	m_animating = true;
	m_extended = extended;
	backgroundanimation = 0;

	m_nextView = Views::NOCHANGE;
	m_background.setFillColor(MyColors.Transparent);
	m_background.setPosition(0,0);
	m_background.setSize(sf::Vector2f((float)screensize.x, (float)screensize.y));

	m_exitbutton = new StandardButton(Vector2f(0,0), Vector2f(MENU_WIDTH,50), "Exit", 0, false);
	m_exitbutton->Attach(this);
	m_DrawV.push_back(m_exitbutton);
	m_AnimateV.push_back(m_exitbutton);
	m_ClickV.push_back(m_exitbutton);

	m_continuebutton = new StandardButton(Vector2f(0,0), Vector2f(MENU_WIDTH,50), "Resume", 1, false);
	m_continuebutton->Attach(this);
	m_DrawV.push_back(m_continuebutton);
	m_AnimateV.push_back(m_continuebutton);
	m_ClickV.push_back(m_continuebutton);

	m_volumetext = new Textblock(Vector2f(0,0), Vector2f(MENU_WIDTH,50), "Volume", 20);
	m_volumetext->setFillColor(MyColors.Transparent);
	m_volumetext->setFontColor(MyColors.White);
	m_DrawV.push_back(m_volumetext);
																//TODO get the actual volume for the slider
	m_volumeslider = new Slider(true, Vector2f(MENU_WIDTH, 30), 1, Vector2f(0,0), 0);
	m_volumeslider->Attach(this);
	m_DrawV.push_back(m_volumeslider);
	m_ClickV.push_back(m_volumeslider);

	m_pGraphics = new SpriteTex[3];

	Image img;
	if(!img.loadFromFile("Data/images/menu_top.png"))
		std::cout << "MenuView.cpp : load menu_top.png failed";
	m_pGraphics[0].t.loadFromImage(img);
	if(!img.loadFromFile("Data/images/menu_mid.png"))
		std::cout << "MenuView.cpp : load menu_mid.png failed";
	m_pGraphics[1].t.loadFromImage(img);
	if(!img.loadFromFile("Data/images/menu_bot.png"))
		std::cout << "MenuView.cpp : load menu_bot.png failed";
	m_pGraphics[2].t.loadFromImage(img);

	for(int i = 0; i < 3; i++)
	{
		m_pGraphics[i].t.setSmooth(false);
		m_pGraphics[i].t.setRepeated(true);
		m_pGraphics[i].s.setTexture(&m_pGraphics[i].t, true);
	}
	m_pGraphics[0].s.setSize(Vector2f(240,150));
	/*TEMP*/ m_pGraphics[1].s.setSize(Vector2f(240,150));
	m_pGraphics[2].s.setSize(Vector2f(240,150));

	positionElements(screensize);

	m_pMS = MS;
}

void MenuView::positionElements(Vector2u & size)
{
	//TODO SET MENU MID HEIGHT DYNAMICALLY

	Vector2f refPoint = Vector2f(((float)size.x - MENU_WIDTH) / 2, 0);

	m_pGraphics[0].s.setPosition(refPoint.x - MENU_BORDERSPACING, refPoint.y);

	refPoint.y +=  150;

	m_pGraphics[1].s.setPosition(refPoint.x - MENU_BORDERSPACING, refPoint.y);

	m_continuebutton->setPosition(refPoint.x , refPoint.y);

	refPoint.y  += 60;

	m_volumetext->setPos(Vector2f(refPoint.x + MENU_WIDTH / 2 - m_volumetext->getSize().x / 2, refPoint.y));

	refPoint.y += 20;

	m_volumeslider->setPosition(refPoint);

	refPoint.y += 60;

	m_exitbutton->setPosition(refPoint);

	m_pGraphics[2].s.setPosition(refPoint.x - MENU_BORDERSPACING,m_pGraphics[1].s.getPosition().y + m_pGraphics[1].s.getSize().y);

}

MenuView::~MenuView(void)
{
	delete m_exitbutton;
	delete m_continuebutton;
	delete m_volumeslider;
	delete m_volumetext;

	delete[] m_pGraphics;
}

void MenuView::onButtonClick(int id)
{
	switch (id)
	{
	case 0:
		m_nextView = Views::CLOSE;
		break;

	case 1:
		m_nextView = Views::MENU;
		break;
	
	default:
		break;
	}
}

void MenuView::onSliderValueChange(int ID, double position)
{
	m_pMS->set_volume(generel_noise, position*100);
}

void MenuView::onSliderReleased(int ID, double position)
{
	std::cout << "Lautstärke jetzt: " << position*100 << std::endl;
}


bool MenuView::MouseMoved(sf::Vector2i & mouse)
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->MouseMoved(mouse))
			return true;
	return false;
}

bool MenuView::PressedRight()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedRight())
			return true;
	return false;
}

bool MenuView::PressedLeft()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedLeft())
			return true;
	return false;
}

bool MenuView::ReleasedRight()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->ReleasedRight())
			return true;
	return false;
}

bool MenuView::ReleasedLeft()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->ReleasedLeft())
			return true;
	return false;
}
	
void MenuView::animationTick()
{
	for(unsigned int i = 0; i < m_AnimateV.size(); i++)
		m_AnimateV[i]->animationTick();

	if(m_animating)
	{
		m_background.setFillColor(Color(0,0,0,(Uint8)(static_cast<float>(backgroundanimation) /  MENU_ANIMATIONTIME * 230)));
		backgroundanimation++;
		if(backgroundanimation > MENU_ANIMATIONTIME)
			m_animating = false;
	}
}
	
void MenuView::onKeyDown(sf::Event e)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onKeyDown(e);
}

void MenuView::onKeyUp(sf::Event e)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onKeyUp(e);
}
void MenuView::onTextInput(std::string s)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onTextInput(s);
}

void MenuView::draw(sf::RenderWindow* rw)
{
	rw->draw(m_background);
	for(int i = 0; i < 3; i++)
		rw->draw(m_pGraphics[i].s);

	for(unsigned int i = 0; i < m_DrawV.size(); i++)
		m_DrawV[i]->draw(rw);	
}

Views MenuView::nextState()
{
	return m_nextView;
}

void MenuView::pt1zyklisch(double elpasedMs)
{
	//BURAK GOES HERE
}

void MenuView::onResize(Vector2u & size)
{
	positionElements(size);
}

Views MenuView::getType()
{
	return Views::MENU;
}

