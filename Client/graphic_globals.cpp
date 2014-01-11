#include "graphic_globals.h"


sf::Font* MyFonts::s_pArial = NULL;


MyFonts::MyFonts()
{
	
}

sf::Font & MyFonts::getFont(GameFonts f)
{
	switch (f)
	{
	case ARIAL:
		if(s_pArial == NULL)
		{
			std::cout << " LOADING FONT ARIAL " << std::endl;
			
			s_pArial = new Font();
			if(!s_pArial->loadFromFile("Data/Fonts/arial.ttf"))
				std::cout << "font arial load failed!!" << std::endl;
		}
		else 
			std::cout << " FONT ALREADY LOADED " << std::endl;
		
		return *s_pArial;
		break;
	default:
		break;
		
	}	
}

void MyFonts::deleteFonts()
{
	if(s_pArial != NULL)
		delete s_pArial;
}
