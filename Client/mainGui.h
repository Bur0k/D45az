#ifndef MAINGUI_H
#define MAINGUI_H

#include <iostream>
#include <vector>
#include "graphic_globals.h"
#include "IClickable.h"
#include "StandardButton.h"
#include "Unit.h"
#include "UnitGroup.h"
#include "City.h"
#include "IDrawable.h"

#define SELECTARMY 0
#define SELECTCITY 1
#define DEFENSIVE 2
#define AGRESSIVE 3
#define HURRY 4
#define MAINGUI_HEIGHT 250
#define MAINGUI_HEIGHT_HIDDEN 50 

class mainGui
	: public IClickable, public IButtonfunction, public IDrawable, public IAnimatable
{
private:
	SpriteTex background;
	std::vector<Unit*> units;
	StandardButton* select_army;
	StandardButton* select_city;
	StandardButton* army_mode[3];

	void positionGraphics();

	bool mouseOver;
	
	bool hidden;
	
public:
	float y_offset;

	bool has_army;
	bool has_city;
	bool army_display;
	

	mainGui();
	~mainGui();

	void updateMgui();
	void onResize(sf::Vector2u);
	City* city;
	UnitGroup* group;

	//iclickablese
	bool MouseMoved(sf::Vector2i &);
	bool PressedRight();
	bool PressedLeft();
	bool ReleasedRight();
	bool ReleasedLeft();

	//ibuttonfunction
	void onButtonClick(int);
	//idrawable
	void draw(sf::RenderWindow* rw);
	//ianimatable
	void animationTick();

};



#endif //MAINGUI_H