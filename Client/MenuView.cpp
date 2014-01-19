#include "MenuView.h"


MenuView::MenuView(Vector2u & screensize)
{
	backgroundanimation = 0;
	m_nextView = Views::NOCHANGE;
	m_background.setFillColor(MyColors.Transparent);
	m_background.setPosition(0,0);
	m_background.setSize(sf::Vector2f((float)screensize.x, (float)screensize.y));

	m_exitbutton = new StandardButton(Vector2f((float)screensize.x / 2, (float)screensize.y / 2), Vector2f(150,50),"Exit",0,false);
	m_exitbutton->Attach(this);
	m_DrawV.push_back(m_exitbutton);
	m_AnimateV.push_back(m_exitbutton);
	m_ClickV.push_back(m_exitbutton);

}

void MenuView::centering(Vector2u & size)
{
	Vector2f midPoint = Vector2f((float)size.x / 2, (float)size.y);
	
	
}

MenuView::~MenuView(void)
{
	delete m_exitbutton;
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
		m_background.setFillColor(Color(0,0,0,(Uint8)(static_cast<float>(backgroundanimation) /  MENUANIMATIONTIME * 230)));
		backgroundanimation++;
		if(backgroundanimation > MENUANIMATIONTIME)
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

	for(unsigned int i = 0; i < m_DrawV.size(); i++)
		m_DrawV[i]->draw(rw);	
}

Views MenuView::nextState()
{
	//TODO do something 

	return m_nextView;
}

void MenuView::update(double elpasedMs)
{

}

void MenuView::onResize(Vector2u & size)
{
	centering(size);
}

Views MenuView::getType()
{
	return Views::MENU;
}

