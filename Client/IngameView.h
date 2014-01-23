#ifndef INGAMEVIEW_H
#define INGAMEVIEW_H

#include <vector>
#include <SFML\Graphics.hpp>
#include "IView.h"
#include "StandardButton.h"
#include "Slider.h"
#include "Textblock.h"
#include "Textbox.h"
#include "Unit.h"
#include "Map.h"
#include "Statusbar.h"
#include "CommitButton.h"

#define INGAMEVIEW_MAX_MAPSPEED  20
#define INGAMEVIEW_MOUSEOVER_RECT_BORDER 3

enum IngameViewButtonId{
	COMMIT = 0,
};

enum InagameViewPhases{
	YOURTURN,
	WAITFORPLAYERS,
	WATCHRESULTS,
	GAMEOVER
};


class IngameView : 
	public IView, public IButtonfunction, public ISliderFunction, public ITextBoxFunction
{
private:

	//debug

	Unit* u, * u1;

	//debug off

	//is filled with the army that is currently selected
	std::vector<Unit*> UnitVector;

	CommitButton* m_commitB;

	//MAP STUFF
	Map m_map;
	IntRect m_mapView;
	Vector2i m_mapSize;
	Vector2i m_tileSize;
	//pixels
	Vector2i m_mapTotalSize;

	//scrolling the map
	Vector2i m_scrolldir;
	Vector2f m_scrollspeed;

	DrawVect m_DrawV;
	AnimateVect m_AnimateV;
	ClickVect m_ClickV;
	KeyInputVect m_KeyV;

	Views m_nextView;

	Statusbar* m_SBar;

	InagameViewPhases m_phase;
	
	RectangleShape m_mapMouseOver;

public:
	IngameView(Vector2u & screensize, StatusBarFunctions* SBar_Function);
	~IngameView();

	//param x : -1, 0, +1
	//param y : same
	void setScrollDirection(int x, int y);

	void draw(sf::RenderWindow* rw);

	bool MouseMoved(sf::Vector2i &);
	bool PressedRight();
	bool PressedLeft();
	bool ReleasedRight();
	bool ReleasedLeft();
	
	void animationTick(); 
	//IKey
	void onKeyDown(sf::Event);
	void onKeyUp(sf::Event);
	void onTextInput(std::string s);

	void onResize(sf::Vector2u &);
	void pt1zyklisch(double elpasedMs);

	Views getType();

	Views nextState();
	//IClickable
	void onButtonClick(int);
	void onSliderValueChange(int ID, double position);
	void onSliderReleased(int ID, double position);
	void onTextBoxSend(int ID, std::string s);

private:
	//gets called from Update if nex phase is required 
	void nextPhase();
	void moveMap();
};





#endif //INGAMEVIEW_H