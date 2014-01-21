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


class IngameView : 
	public IView, public IButtonfunction, public ISliderFunction, public ITextBoxFunction
{
private:

	//debug

	Unit* u, * u1;

	//debug off

	//is filled with the army that is currently selected
	std::vector<Unit*> UnitVector;

	Map m_map;
	Vector2f m_mapSize;
	IntRect m_mapView;
	Vector2i m_tileSize;

	DrawVect m_DrawV;
	AnimateVect m_AnimateV;
	ClickVect m_ClickV;
	KeyInputVect m_KeyV;

	Views m_nextView;

public:
	IngameView(Vector2u & screensize);
	~IngameView();

	
	

	void draw(sf::RenderWindow* rw);

	bool MouseMoved(sf::Vector2i &);
	bool PressedRight();
	bool PressedLeft();
	bool ReleasedRight();
	bool ReleasedLeft();
	
	void animationTick(); 
	
	void onKeyDown(sf::Event);
	void onKeyUp(sf::Event);
	void onTextInput(std::string s);

	void onResize(sf::Vector2u &);
	void update(double elpasedMs);

	Views getType();

	Views nextState();

	void onButtonClick(int);
	void onSliderValueChange(int ID, double position);
	void onSliderReleased(int ID, double position);
	void onTextBoxSend(int ID, std::string s);
};





#endif //INGAMEVIEW_H