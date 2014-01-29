#include "LoginView.h"


LoginView::LoginView(Vector2u & size)
{

	//create all the ui elements here
	
	logintext = new Textblock(Vector2f(100,100),Vector2f(500,70),"LOGIN SCREEN", 50);
	logintext->setFillColor(MyColors.Red);

	m_DrawV.push_back(logintext);

	status= new Textblock(Vector2f(100,600),Vector2f(700,70),"", 40);
	status->setFontColor(MyColors.Red);
	status->setBackgroundColor(MyColors.Transparent);
	m_DrawV.push_back(status);

	name = new TextBox(200,"Enter name",sf::Vector2f(100,200),false,1);
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
	
	bg.onResize(size);
	
	/*if(!image.loadFromFile("Data/Images/Button.png"))
		std::cout << "LoginView.cpp:  couldn't load Button.png" << std::endl;/**/
	
	

	centering(size);
	
	NL = nullptr;

	connected = false;
	connect = new Connect();
}

LoginView::~LoginView()
{
	delete name;
	delete lgoinbutton;
	delete logintext;
	delete status;
	if(NL!=nullptr)
		delete NL;
	if(connect!=nullptr)
		delete connect;
}

void LoginView::onButtonClick(int)
{
	if(connected)
	{
		std::string s;
		s = name->getText();
		if(NL==nullptr)
		{
			playerData.Name = s;
			NL = new Login(s);
			status->setText("",sf::Vector2f());
		}
	}
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
	bg.draw(rw);

	for(unsigned int i = 0; i < m_DrawV.size(); i++)
		m_DrawV[i]->draw(rw);	
}

Views LoginView::nextState()
{
	return next;
}

void LoginView::update(double elapsedMs)
{
	if(!connected && connect != nullptr)
	{
		if(connect->getState()==1)
		{
			connected = true;
			delete connect;
			connect = nullptr;
		}
		else if(connect->getState()==-1)
		{
			status->setText("Network connection failed:\n"+connect->getErrorMsg(),Vector2f(700,70));
			delete connect;
			connect = nullptr;
		}
	}
	else if(NL != nullptr)
	{
		if(NL->getState() == 1)
			next = Views::LOBBY;
		else if(NL->getState() == -2)
		{
			status->setText("Minimal 4 and maximal 10 characters.\nPlease choose a different name.",Vector2f(700,70));
			delete NL;
			NL = nullptr;
		}
		else if(NL->getState() == -1)
		{
			status->setText("Name is already in usage.\nPlease choose a different name.",Vector2f(700,70));
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
	lgoinbutton->setPosition(size.x / 2.0f - lgoinbutton->getSize().x / 2.0f, name->getPos().y + name->getSize().y + 0.05f * size.y);
	logintext->setPos(sf::Vector2f(size.x / 2.0f - logintext->getSize().x / 2.0f, name->getPos().y - 0.05f * size.y - logintext->getSize().y));

	bg.onResize(size);
}

Views LoginView::getType()
{
	return Views::LOGIN;
}
