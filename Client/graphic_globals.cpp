#include "graphic_globals.h"


sf::Font* MyFonts::s_pArial = NULL;


MyFonts::MyFonts()
{
	
}

sf::Font & MyFonts::getFont(GameFonts f)
{
	switch (f)
	{
	case GameFonts::ARIAL:
		if(s_pArial == NULL)
		{
			std::cout << "loading Font: Arial" << std::endl;
			
			s_pArial = new Font();
			if(!s_pArial->loadFromFile("Data/Fonts/arial.ttf"))
				std::cout << "graphic_globals.cpp : font arial load failed!!" << std::endl;
		}
		
		return *s_pArial;
		break;
	default:
		//in case font is not yet implemented return arial
		return MyFonts::getFont(GameFonts::ARIAL);
		break;
		
	}	
}

void MyFonts::deleteFonts()
{
	if(s_pArial != NULL)
		delete s_pArial;
	s_pArial = NULL;
}
