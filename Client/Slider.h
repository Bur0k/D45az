#ifndef SLIDER_H
#define SLIDER_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <vector>

using namespace sf;


class ISliderFunction
{
	virtual void onSliderValueChange(int ID, double position)=0;
};

typedef std::vector<ISliderFunction*> SliderCallbackTarget;

class Slider
{
protected:
	sf::Rect<float> m_dimensions;
	int m_ID;
	SliderCallbackTarget attachedfuncs;
	
	
	void Notify();

public:
	Slider(bool horizontal, float size, Vector2f pos, int id);

	void Attach(ISliderFunction*);
	bool Detach(ISliderFunction*);
	
};

#endif