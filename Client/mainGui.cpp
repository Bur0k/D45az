#include "mainGui.h"


mainGui::mainGui():
	cityLevel(sf::Vector2f(0,0),sf::Vector2f(0,0),"",18),
	cityIncome(sf::Vector2f(0,0),sf::Vector2f(0,0),"",18)
{
	Image img;
	if(!img.loadFromFile("Data/Images/mainGui.png"))
		std::cout << "maingui.cpp : failed to load Data/Images/mainGui.png" << std::endl;

	background.t.loadFromImage(img);
	background.t.setSmooth(true);
	background.s.setTexture(& background.t);
	background.s.setSize((Vector2f)img.getSize());

	select_army = new StandardButton(Vector2f(0,0),Vector2f(100,30),std::string("Army"), MAINGUI_SELECTARMY,true);
	select_army->setIsEnabled(false);
	select_army->Attach(this);
	select_city = new StandardButton(Vector2f(0,0),Vector2f(100,30),std::string("City"), MAINGUI_SELECTCITY,true);
	select_city->setIsEnabled(false);
	select_city->Attach(this);

	army_mode[0] = new StandardButton(Vector2f(0,0),Vector2f(100,30),std::string("defensive"), MAINGUI_DEFENSIVE,false,false);
	army_mode[0]->Attach(this);
	army_mode[1] = new StandardButton(Vector2f(0,0),Vector2f(100,30),std::string("agressive"), MAINGUI_AGRESSIVE,false,false);
	army_mode[1]->Attach(this);
	army_mode[2] = new StandardButton(Vector2f(0,0),Vector2f(100,30),std::string("fast"), MAINGUI_HURRY,false,false);
	army_mode[2]->Attach(this);

	deleteMove = new StandardButton(Vector2f(0,0),Vector2f(100,30),std::string("undo Move"), MAINGUI_UNDO_MOVE,false,false);
	deleteMove->Attach(this);


	hidden = true;
	has_army = false;
	has_city = false;
	mouseOver = false;

	city = NULL;
	group = NULL;

	army_display = true;
	city_display = false;

	cityLevel.setBackgroundColor(MyColors.Transparent);
	cityIncome.setBackgroundColor(MyColors.Transparent);
	cityUnits.push_back(new Unit(sf::Vector2f(0,0),UnitTypes::LIGHT,0));
	cityUnits.push_back(new Unit(sf::Vector2f(0,0),UnitTypes::HEAVY,0));
	cityUnits.push_back(new Unit(sf::Vector2f(0,0),UnitTypes::LONGRANGE,0));
	cityUnits.push_back(new Unit(sf::Vector2f(0,0),UnitTypes::ARTILLERY,0));
	cityUnityBuy.push_back(new StandardButton(Vector2f(0,0),Vector2f(60,30),std::string("Light"), maingui_light,false,false));
	cityUnityBuy.push_back(new StandardButton(Vector2f(0,0),Vector2f(60,30),std::string("Heavy"), maingui_heavy,false,false));
	cityUnityBuy.push_back(new StandardButton(Vector2f(0,0),Vector2f(60,30),std::string("Longrange"), maingui_longrange,false,false));
	cityUnityBuy.push_back(new StandardButton(Vector2f(0,0),Vector2f(60,30),std::string("Artillery"), maingui_artillery,false,false));
	cityUnityBuy.push_back(new StandardButton(Vector2f(0,0),Vector2f(60,30),std::string("Cityupgrade"), maingui_city,false,false));

	for(auto it : cityUnityBuy)
		it->Attach(this);
	currentCityActionsIndex=0;
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

	for(Unit* u : units)
		delete u;

	units.clear();

	for(auto it : cityUnits)
		delete it;
	for(auto it : cityUnityBuy)
		delete it;
}

void mainGui::positionGraphics()
{
	float y_origin = y_offset - ((hidden)? MAINGUI_HEIGHT_HIDDEN : MAINGUI_HEIGHT);
	background.s.setPosition(0, y_origin);
	select_army->setPosition(50, y_origin + 25);
	select_city->setPosition(200, y_origin + 25);

	for(unsigned int i = 0; i < units.size(); i++)
		units[i]->setPosition(Vector2f(20 + 70 * (float)(i % 8), (i < 7)? y_offset - 186 : y_offset - 92));

	for(int i = 0; i < 3; i++)
		army_mode[i]->setPosition(Vector2f(600,y_origin + 90 + i * 40));
	
	deleteMove->setPosition(Vector2f(600, y_origin + 90 + 120));

	if(currentCityActionsIndex < updateInfo.size())
		cityIncome.setText("Income: "+to_string(city->generatedIncome),sf::Vector2f(1000,1000));
	if(currentCityActionsIndex < updateInfo.size())
		cityLevel.setText("Level: "+to_string(city->level),sf::Vector2f(1000,1000));
	cityLevel.setPos(sf::Vector2f(30,y_origin+75));
	cityIncome.setPos(sf::Vector2f(30,y_origin+100));

	int startX = 150;
	
	for(unsigned int i=0;i<cityUnits.size();i++)
	{
		cityUnits[i]->setPosition(sf::Vector2f((float)startX,y_origin+75));
		cityUnityBuy[i]->setPosition(sf::Vector2f((float)startX,y_origin+175));
		startX+=75;
	}
	cityUnityBuy[cityUnits.size()]->setPosition(sf::Vector2f(startX,y_origin+175));
}

void mainGui::updateMgui(City* city, UnitGroup* army)
{
	if(city != NULL)
	{
		this->city = city;
		has_city = true;
		
	}
	if(army != NULL)
	{
		this->group = army;
		has_army = true;
		
	}

	
	select_city->setIsEnabled(has_city);
	if(!has_city)
		select_city->unLock();
	select_army->setIsEnabled(has_army);
	
	if(!has_army)
		select_army->unLock();

	bool oldhidden = hidden;

	if(!has_city && !has_army)
		hidden = true;


	if(hidden != oldhidden)
		positionGraphics();
	

	select_city->animation_upadate();
	select_army->animation_upadate();
}

bool mainGui::MouseMoved(sf::Vector2i & mouse)
{
	bool retvalue;
	retvalue |= select_army->MouseMoved(mouse);
	retvalue |= select_city->MouseMoved(mouse);

	if(army_display && has_army)
	{
		if(!hidden)
			for(int i = 0; i < 3; i++)
				retvalue |= army_mode[i]->MouseMoved(mouse);
		for(Unit* u : units)
			retvalue |= u->MouseMoved(mouse);
		retvalue |= deleteMove->MouseMoved(mouse);
	}
	if(city_display)
		for(auto it : cityUnityBuy)
			it->MouseMoved(mouse);
	return retvalue;
}

bool mainGui::PressedLeft()
{
	bool retvalue;
	
	retvalue |= select_army->PressedLeft();
	retvalue |= select_city->PressedLeft();

	if(army_display && has_army)
	{
		if(!hidden)
			for(int i = 0; i < 3; i++)
				retvalue |= army_mode[i]->PressedLeft();
		for(Unit* u : units)
			retvalue |= u->PressedLeft();

		retvalue |= deleteMove->PressedLeft();
	}
	if(city_display)
		for(auto it : cityUnityBuy)
			it->PressedLeft();
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

		retvalue |= deleteMove->ReleasedLeft();
	}
	if(city_display)
		for(auto it : cityUnityBuy)
			it->ReleasedLeft();
	return retvalue;
}

void mainGui::onButtonClick(int id)
{
	switch (id)
	{
	case MAINGUI_SELECTARMY:
		if(has_army && select_army->getIsPressed())
		{
			army_display = true;
			hidden = city_display = false;
			positionGraphics();
			
			displayArmy();
			
			select_city->unLock();
		}
		else if(!select_city->getIsPressed() && !select_army->getIsPressed())
		{
			hidden = true;
			positionGraphics();
		}
		break;

	case MAINGUI_SELECTCITY:
		if(has_city && select_city->getIsPressed())
		{
			army_display = hidden = false;
			city_display = true;
			positionGraphics();

			displayCity();

			select_army->unLock();
		}
		else if(!select_city->getIsPressed() && !select_army->getIsPressed())
		{
			hidden = true;
			positionGraphics();
		}
		break;

	case MAINGUI_DEFENSIVE:
		if(group->strategy != UnitStrategy::DEFENSIVE)
		{
			resetModeButtons();
			army_mode[0]->m_color = MyColors.Chartreuse;
			group->strategy = UnitStrategy::DEFENSIVE;
			if(deleteMoveFunction != NULL)
				deleteMoveFunction->deleteMoves(group, 7);
		}
		break;

	case MAINGUI_AGRESSIVE:
		if(group->strategy != UnitStrategy::OFFENSIVE)
		{
			resetModeButtons();
			army_mode[1]->m_color = MyColors.Chartreuse;
			group->strategy = UnitStrategy::OFFENSIVE;
			if(deleteMoveFunction != NULL)
				deleteMoveFunction->deleteMoves(group, 10);
		}
		break;

	case MAINGUI_HURRY:
		if(group->strategy != UnitStrategy::RUNNING)
		{
			resetModeButtons();
			army_mode[2]->m_color = MyColors.Chartreuse;
			group->strategy = UnitStrategy::RUNNING;
			if(deleteMoveFunction != NULL)
				deleteMoveFunction->deleteMoves(group, 15);
		}
		break;

	case MAINGUI_UNDO_MOVE:
		if(deleteMoveFunction != NULL)
			deleteMoveFunction->deleteMoves(group, -1);
		break;

	case maingui_light:
		if(statusbar->m_vValue[0] >= lightPrice)
		{
			statusbar->setValue(Icons::MONEY, statusbar->m_vValue[0] - lightPrice);
			cityUnityBuy[1]->setIsEnabled(false);
			cityUnityBuy[2]->setIsEnabled(false);
			cityUnityBuy[3]->setIsEnabled(false);
			updateInfo[currentCityActionsIndex].numOfProducingUnit = cityUnits[0]->getNumberOfSoldiers()+1;
			cityUnits[0]->setNumberOfSoldiers(updateInfo[currentCityActionsIndex].numOfProducingUnit);
			updateInfo[currentCityActionsIndex].ProducedUnit = UnitTypes::LIGHT;
			positionGraphics();
		}
		break;

	case maingui_heavy:
		if(statusbar->m_vValue[0] >= heavyPrice)
		{
			statusbar->setValue(Icons::MONEY, statusbar->m_vValue[0] - heavyPrice);
			cityUnityBuy[0]->setIsEnabled(false);
			cityUnityBuy[2]->setIsEnabled(false);
			cityUnityBuy[3]->setIsEnabled(false);
			updateInfo[currentCityActionsIndex].numOfProducingUnit = cityUnits[1]->getNumberOfSoldiers()+1;
			cityUnits[1]->setNumberOfSoldiers(updateInfo[currentCityActionsIndex].numOfProducingUnit);
			updateInfo[currentCityActionsIndex].ProducedUnit = UnitTypes::HEAVY;
			positionGraphics();
		}
		break;

	case maingui_longrange:
		if(statusbar->m_vValue[0] >= longrangePrice)
		{
			statusbar->setValue(Icons::MONEY, statusbar->m_vValue[0] - longrangePrice);
			cityUnityBuy[0]->setIsEnabled(false);
			cityUnityBuy[1]->setIsEnabled(false);
			cityUnityBuy[3]->setIsEnabled(false);
			updateInfo[currentCityActionsIndex].numOfProducingUnit = cityUnits[2]->getNumberOfSoldiers()+1;
			cityUnits[2]->setNumberOfSoldiers(updateInfo[currentCityActionsIndex].numOfProducingUnit);
			updateInfo[currentCityActionsIndex].ProducedUnit = UnitTypes::LONGRANGE;
			positionGraphics();
		}
		break;

	case maingui_artillery:
		if(statusbar->m_vValue[0] >= artilleryPrice)
		{
			statusbar->setValue(Icons::MONEY, statusbar->m_vValue[0] - artilleryPrice);
			cityUnityBuy[0]->setIsEnabled(false);
			cityUnityBuy[1]->setIsEnabled(false);
			cityUnityBuy[2]->setIsEnabled(false);
			updateInfo[currentCityActionsIndex].numOfProducingUnit = cityUnits[3]->getNumberOfSoldiers()+1;
			cityUnits[3]->setNumberOfSoldiers(updateInfo[currentCityActionsIndex].numOfProducingUnit);
			updateInfo[currentCityActionsIndex].ProducedUnit = UnitTypes::ARTILLERY;
			positionGraphics();
		}
		break;

	case maingui_city:
		if(statusbar->m_vValue[0] >= cityUpgrade)
		{
			statusbar->setValue(Icons::MONEY, statusbar->m_vValue[0] - cityUpgrade);
			updateInfo[currentCityActionsIndex].updating = true;
			cityUnityBuy[4]->setIsEnabled(false);
			positionGraphics();
		}
		break;

	default:
		break;
	}

	for(int i = 0; i < 3; i++)
		army_mode[i]->animation_upadate();

	if(!select_army->getIsPressed() && !select_city->getIsPressed())
		hidden = true;
	else 
		hidden = false;

}

bool mainGui::PressedRight(){  return false; }
bool mainGui::ReleasedRight(){ return false; }


void mainGui::draw(sf::RenderWindow* rw)
{
	rw->draw(background.s);
	select_army->draw(rw);
	select_city->draw(rw);
	
	
	if(army_display && has_army && !hidden)
	{
		for(int i = 0; i < 3; i++)
			army_mode[i]->draw(rw);
		for(Unit* u : units)
			u->draw(rw);

		deleteMove->draw(rw);
	}
	else if(city_display)
	{
		cityIncome.draw(rw);
		cityLevel.draw(rw);
		for(auto it : cityUnits)
			it->draw(rw);
		for(auto it : cityUnityBuy)
			it->draw(rw);

		
	}
}

void mainGui::onResize(sf::Vector2u size)
{
	y_offset = static_cast<float>(size.y);
	positionGraphics();
}

void mainGui::animationTick()
{
	select_army->animationTick();
	select_city->animationTick();
	for(int i = 0; i < 3; i++)
		army_mode[i]->animationTick();
	if(city_display)
		for(auto it : cityUnityBuy)
			it->animationTick();
	deleteMove->animationTick();
}

void mainGui::displayArmy()
{
	for(Unit* u : units)
		delete u;
	units.clear();


	for(int i = 0; i < 16; i++)
		if(group->units[i].count > 0)
			units.push_back(new Unit(Vector2f(0,0),group->units[i].type,group->units[i].count));

	void resetModeButtons();
	switch (group->strategy)
	{
	case UnitStrategy::DEFENSIVE:
		army_mode[0]->m_color = MyColors.Chartreuse;
		break;

	case UnitStrategy::OFFENSIVE:
		army_mode[1]->m_color = MyColors.Chartreuse;
		break;

	case UnitStrategy::RUNNING:
		army_mode[2]->m_color = MyColors.Chartreuse;
		break;	
	
	default:
		break;
	}
	
	positionGraphics();
}

void mainGui::resetModeButtons()
{
	for(int i = 0; i < 3; i++)
	{
		army_mode[i]->m_color = MyColors.ButtonColor;
		army_mode[i]->animation_upadate();
	}

}


void mainGui::displayCity()
{
	bool isAlreadyDefined = false;
	for(unsigned int i=0;i<updateInfo.size();i++)
	{
		if(updateInfo[i].pos == city->position)
		{

			isAlreadyDefined = true;
			currentCityActionsIndex = static_cast<int>(currentCityActionsIndex);
			if(updateInfo[i].updating)
				cityUnityBuy[4]->setIsEnabled(false);
			else
				cityUnityBuy[4]->setIsEnabled(true);

			if(updateInfo[i].numOfProducingUnit != 0)
			{
				cityUnityBuy[0]->setIsEnabled(false);
				cityUnityBuy[1]->setIsEnabled(false);
				cityUnityBuy[2]->setIsEnabled(false);
				cityUnityBuy[3]->setIsEnabled(false);
				switch(updateInfo[i].ProducedUnit)
				{
				case UnitTypes::LIGHT:cityUnityBuy[0]->setIsEnabled(true);break;
				case UnitTypes::HEAVY:cityUnityBuy[1]->setIsEnabled(true);break;
				case UnitTypes::LONGRANGE:cityUnityBuy[2]->setIsEnabled(true);break;
				case UnitTypes::ARTILLERY:cityUnityBuy[3]->setIsEnabled(true);break;
				}
			}
			else
			{
				cityUnityBuy[0]->setIsEnabled(true);
				cityUnityBuy[1]->setIsEnabled(true);
				cityUnityBuy[2]->setIsEnabled(true);
				cityUnityBuy[3]->setIsEnabled(true);
			}

			break;
		}
	}
	if(!isAlreadyDefined)
	{
		cityUnityBuy[0]->setIsEnabled(true);
		cityUnityBuy[1]->setIsEnabled(true);
		cityUnityBuy[2]->setIsEnabled(true);
		cityUnityBuy[3]->setIsEnabled(true);
		cityUnityBuy[4]->setIsEnabled(true);

		currentCityActionsIndex = updateInfo.size();

		CityActions ca;
		ca.numOfProducingUnit=0;
		ca.pos=city->position;
		ca.ProducedUnit=UnitTypes::ARTILLERY;
		ca.updating=false;

		updateInfo.push_back(ca);
	}

	positionGraphics();
}

std::vector<unsigned char> mainGui::getCityActionData()
{
	// Message: (Position x city, Position y city, Anzahl Truppen Group, Unittype, bool cityUpgrade, playerID,...)

	std::vector<unsigned char> toSend;


	for(auto it : updateInfo)
	{
		toSend.push_back(static_cast<char>(city->player_ID));
		toSend.push_back(static_cast<char>(it.pos.x));
		toSend.push_back(static_cast<char>(it.pos.y));
		toSend.push_back(static_cast<char>(it.numOfProducingUnit));
		toSend.push_back(static_cast<char>(it.ProducedUnit));
		toSend.push_back(static_cast<char>(it.updating));
	}


	updateInfo.clear();
	return toSend;
}


void  mainGui::Clear()
{
	resetModeButtons();
	group = NULL;
	city = NULL;

	for(Unit* u : units)
		delete u;

	units.clear();

	select_city->unLock();
	select_army->unLock();

	select_city->setIsEnabled(false);
	select_army->setIsEnabled(false);

	hidden = true;

	positionGraphics();

	updateInfo.clear();
	for(auto it : cityUnits)
		it->setNumberOfSoldiers(0);
	for(auto it : cityUnityBuy)
		it->setIsEnabled(true);
}
