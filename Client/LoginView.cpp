#include "LoginView.h"


LoginView::LoginView()
{

	//create all the ui elements here
	logintext.setFont(MyFonts::getFont(GameFonts::ARIAL));
	logintext.setPosition(100,100);
	logintext.setString("LOGIN");
	logintext.setCharacterSize(50);
	
	name = new TextBox(200,"enter name",sf::Vector2f(100,200),true,1);
	name->attach(this);
	m_DrawV.push_back(name);
	m_AnimateV.push_back(name);
	m_ClickV.push_back(name);
	m_KeyV.push_back(name);
	
	lgoinbutton = new StandardButton(Vector2f(100,300),Vector2f(100,70),"Login",1,false);
	lgoinbutton->attachFunction(this);
	m_DrawV.push_back(name);
	m_AnimateV.push_back(lgoinbutton);
	m_ClickV.push_back(lgoinbutton);
}

LoginView::~LoginView()
{
	delete name;
	delete lgoinbutton;
}

void LoginView::onButtonClick(int)
{
	//handle incoming clicks here
}

void LoginView::onTextBoxSend(int ID, std::string s)
{
	//recieve shit from textboxes
}


bool LoginView::MouseMooved(sf::Vector2i & mouse)
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->MouseMooved(mouse))
			return true;
	return false;
}

bool LoginView::PressedRight()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedRight())
			return true;
	return false;
}

bool LoginView::PressedLeft()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->PressedLeft())
			return true;
	return false;
}

bool LoginView::ReleasedRight()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->ReleasedRight())
			return true;
	return false;
}

bool LoginView::ReleasedLeft()
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->ReleasedLeft())
			return true;
	return false;
}
	
void LoginView::animationTick()
{
	for(unsigned int i = 0; i < m_AnimateV.size(); i++)
		m_AnimateV[i]->animationTick();
}
	
void LoginView::onKeyDown(sf::Event e)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onKeyDown(e);
}

void LoginView::onKeyUp(sf::Event e)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onKeyUp(e);
}
void LoginView::onTextInput(std::string s)
{
	for(unsigned int i = 0; i < m_KeyV.size(); i++)
		m_KeyV[i]->onTextInput(s);
}

void LoginView::draw(sf::RenderWindow* rw)
{
	for(unsigned int i = 0; i < m_DrawV.size(); i++)
		m_DrawV[i]->draw(rw);
}

Views LoginView::nextState()
{
	//TODO do something 

	return Views::NOCHANGE;
}

void LoginView::onResize(){}