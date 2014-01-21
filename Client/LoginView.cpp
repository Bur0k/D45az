#include "LoginView.h"


LoginView::LoginView(Vector2u & size)
{

	//create all the ui elements here
	
	logintext = new Textblock(Vector2f(100,100),Vector2f(500,70),"LOGIN SCREEN", 50);
	logintext->setFillColor(MyColors.Red);

	m_DrawV.push_back(logintext);

	nameStatus= new Textblock(Vector2f(100,400),Vector2f(500,70),"", 50);
	nameStatus->setFillColor(MyColors.Black);
	nameStatus->setBackgroundColor(MyColors.Transparent);
	m_DrawV.push_back(nameStatus);

	name = new TextBox(200,"enter name",sf::Vector2f(100,200),false,1);
	name->Attach(this);

	m_DrawV.push_back(name);
	m_AnimateV.push_back(name);
	m_ClickV.push_back(name);
	m_KeyV.push_back(name);
	
	lgoinbutton = new StandardButton(Vector2f(100,300),Vector2f(100,70),"Login",1,false);
	lgoinbutton->Attach(this);

	m_DrawV.push_back(lgoinbutton);
	m_AnimateV.push_back(lgoinbutton);
	m_ClickV.push_back(lgoinbutton);

	next = Views::NOCHANGE;
	

	Texture image;
	if(!image.loadFromFile("Data/Images/background.png"))
		std::cout << "LoginView.cpp:  couldn't load background.png" << std::endl;
	
	background.t = image;
	background.s.setTexture(&background.t);                      
	background.s.setPosition(0,0);
	background.s.setSize((sf::Vector2f)image.getSize());

	centering(size);
	
	NL = nullptr;
}

LoginView::~LoginView()
{
	delete name;
	delete lgoinbutton;
	delete logintext;
	delete nameStatus;
	if(NL!=nullptr)
		delete NL;
}

void LoginView::onButtonClick(int)
{
	std::string s;
	s = name->getText();
	if(NL==nullptr)
	{
		NL = new NetworkLogin(s);
		nameStatus->setText("",sf::Vector2f());
	}
	
	//BURAK GOES HERE

}

void LoginView::onTextBoxSend(int ID, std::string s)
{
	onButtonClick(1);
}


bool LoginView::MouseMoved(sf::Vector2i & mouse)
{
	for(unsigned int i = 0; i < m_ClickV.size(); i++)
		if(m_ClickV[i]->MouseMoved(mouse))
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
	rw->draw(this->background.s);

	for(unsigned int i = 0; i < m_DrawV.size(); i++)
		m_DrawV[i]->draw(rw);	
}

Views LoginView::nextState()
{
	//TODO do something 

	return next;
}

void LoginView::update(double elpasedMs)
{
	if(NL != nullptr)
	{
		if(NL->getState() == 1)
			next = Views::LOBBY;
		else if(NL->getState() == -1)
		{
			nameStatus->setText("Name is already in usage.\nPlease choose a different name.",sf::Vector2f(400,400));
			delete NL;
			NL = nullptr;
		}
	}
}

void LoginView::onResize(Vector2u & size)
{
	centering(size);
}


void LoginView::centering(Vector2u & size)
{
	//abstand zwischen den buttons 5% der gesamthöhe

	sf::Vector2f pos(size.x / 2 - name->getSize().x / 2, size.y / 2 - name->getSize().y / 2);
	name->setPos(pos);
	lgoinbutton->setPosition(size.x / 2 - lgoinbutton->getSize().x / 2, name->getPos().y + name->getSize().y + 0.05 * size.y);
	logintext->setPos(sf::Vector2f(size.x / 2 - logintext->getSize().x / 2, name->getPos().y - 0.05 * size.y - logintext->getSize().y));

	background.s.setPosition(size.x / 2 - background.s.getSize().x / 2, size.y /2 - background.s.getSize().y / 2);
}

Views LoginView::getType()
{
	return Views::LOGIN;
}
