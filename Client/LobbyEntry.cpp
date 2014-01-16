#include "LobbyEntry.h"

LobbyEntry::LobbyEntry(Vector2f size, Vector2f pos, std::string name, int players, int maxplayers, int id) 
	: Button(pos,size,"", id,true)
{
	m_dimensions.width = size.x;
	m_dimensions.height = size.y;
	m_dimensions.left = pos.x;
	m_dimensions.top = pos.y;


	m_name.setFont(MyFonts::getFont(GameFonts::ARIAL));
	m_name.setString(name);
	
	m_number.setFont(MyFonts::getFont(GameFonts::ARIAL));


	Text m_name;
	Text m_number;
	int m_maxPlayers;
	int m_players;
	int m_ID;
}


void LobbyEntry::draw(RenderWindow* rw)
{

}