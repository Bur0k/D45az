#include "mainGui.h"


mainGui::mainGui()
{
	Image img;
	if(!img.loadFromFile("Data/Images/mainGui.png"))
		std::cout << "maingui.cpp : failed to load Data/Images/mainGui.png" << std::endl;

	background.t.loadFromImage(img);
	background.t.setSmooth(true);
	background.s.setTexture(& background.t);
	background.s.setSize((Vector2f)img.getSize());

	select_army = new StandardButton(Vector2f(0,0),Vector2f(100,30),std::string("Army"), SELECTARMY,true);
	select_city = new StandardButton(Vector2f(0,0),Vector2f(100,30),std::string("City"), SELECTCITY,true);

	army_mode[0] = new StandardButton(Vector2f(0,0),Vector2f(120,30),std::string("defensive"), DEFENSIVE,false,false);
	army_mode[1] = new StandardButton(Vector2f(0,0),Vector2f(120,30),std::string("agressive"), AGRESSIVE,false,false);
	army_mode[2] = new StandardButton(Vector2f(0,0),Vector2f(120,30),std::string("fast"), HURRY,false,false);

	hidden = true;
	has_army = false;
	has_city = false;

	army_display = true;

	
}


mainGui::~mainGui()
{
	for(auto e : units)
		delete e;
	units.clear();

	delete select_army;
	delete select_city;

	for(int i = 0; i < 3; i++)
		delete army_mode[i];
}

void mainGui::positionGraphics()
{
	float y_origin = y_offset - (hidden)? MAINGUI_HEIGHT_HIDDEN : MAINGUI_HEIGHT;
	background.s.setPosition(0, y_origin);
	select_army->setPosition(50, y_origin + 25);
	select_city->setPosition(50, y_origin + 25);

}

void mainGui::updateMgui()
{

	
	select_city->setIsEnabled(has_city);
	if(!has_city)
		select_city->unLock();
	select_army->setIsEnabled(has_army);
	if(!has_army)
		select_army->unLock();

	if(!has_city && !has_army)
	{
		hidden = true;
	}
}

bool mainGui::MouseMoved(sf::Vector2i & mouse)
{
	bool retvalue;
	retvalue |= select_army->MouseMoved(mouse);
	retvalue |= select_city->MouseMoved(mouse);

	if(army_display && has_army)
	{
		for(int i = 0; i < 3; i++)
			retvalue |= army_mode[i]->MouseMoved(mouse);
		for(Unit* u : units)
			retvalue |= u->MouseMoved(mouse);
	}
	return retvalue;
}

bool mainGui::PressedLeft()
{
	bool retvalue;
	retvalue |= select_army->PressedLeft();
	retvalue |= select_city->PressedLeft();

	if(army_display && has_army)
	{
		for(int i = 0; i < 3; i++)
			retvalue |= army_mode[i]->PressedLeft();
		for(Unit* u : units)
			retvalue |= u->PressedLeft();
	}
	return retvalue;
}

bool mainGui::ReleasedLeft()
{
	bool retvalue;
	retvalue |= select_army->ReleasedLeft();
	retvalue |= select_city->ReleasedLeft();

	if(army_display && has_army)
	{
		for(int i = 0; i < 3; i++)
			retvalue |= army_mode[i]->ReleasedLeft();
		for(Unit* u : units)
			retvalue |= u->ReleasedLeft();
	}
	return retvalue;
}

void mainGui::onButtonClick(int id)
{
	switch (id)
	{
	case SELECTARMY:
		if(has_army && select_army->getIsPressed())
		{
			hidden = false;
			positionGraphics();
			select_city->unLock();
		}
		break;

	case SELECTCITY:
		if(has_city && select_city->getIsPressed())
		{
			hidden = false;
			positionGraphics();
			select_army->unLock();
		}
		break;

	case DEFENSIVE:
		break;

	case AGRESSIVE:
		break;

	case HURRY:
		break;

	default:
		break;
	}



}

bool mainGui::PressedRight(){  return false; }
bool mainGui::ReleasedRight(){ return false; }


void mainGui::draw(sf::RenderWindow* rw)
{
	rw->draw(background.s);
	select_army->draw(rw);
	select_city->draw(rw);
	
	
	if(army_display && has_army)
	{
		for(Unit* u : units)
			u->draw(rw);
	
		for(int i = 0; i < 3; i++)
			rw->draw(*army_mode[i]);
	}
}

void mainGui::onResize(sf::Vector2u size)
{
	y_offset = static_cast<float>(size.y);
}

void mainGui::animationTick()
{
	select_army->animationTick();
	select_city->animationTick();
	for(int i = 0; i < 3; i++)
		army_mode[i]->animationTick();
}
