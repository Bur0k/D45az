#include "LobbyEntry.h"

LobbyEntry::LobbyEntry()
{
	//TODO
}

LobbyEntry::LobbyEntry(Vector2f size, Vector2f pos, std::string name, int players, int maxPlayers, int id) 
	: Button(pos,size,"", id,true)
{
	m_dimensions.width = size.x;
	m_dimensions.height = size.y;
	m_dimensions.left = pos.x;
	m_dimensions.top = pos.y;

	
	
	m_maxPlayers = maxPlayers;
	m_players = players;
	m_ID = id;

	m_nameText.setFont(MyFonts::getFont(GameFonts::ARIAL));
	m_nameText.setString(name);
	m_nameText.setColor(MyColors.Black);
	m_nameText.setPosition(m_dimensions.left + LOBBYENTRYBORDER, m_dimensions.top + LOBBYENTRYBORDER);
	
	m_numberText.setFont(MyFonts::getFont(GameFonts::ARIAL));
	m_numberText.setColor(MyColors.Black);
	
	updatePlayers();
}

void LobbyEntry::updatePlayers()
{
	std::string s;
	s = std::to_string(m_players);
	s += " / ";
	s += std::to_string(m_maxPlayers);
	m_numberText.setString(s);
	sf::Rect<float> textsize = m_numberText.getLocalBounds();
	m_numberText.setPosition(m_dimensions.left + m_dimensions.width - textsize.width - LOBBYENTRYBORDER, m_dimensions.top + LOBBYENTRYBORDER);
}

void LobbyEntry::draw(RenderWindow* rw)
{
	rw->draw(*this);
	rw->draw(m_nameText);
	rw->draw(m_numberText);
	
}

Vector2f LobbyEntry::getSize()
{
	return Vector2f(m_dimensions.width, m_dimensions.height);
}

Vector2f LobbyEntry::getPosition()
{
	return Vector2f(m_dimensions.left, m_dimensions.top);
}

void LobbyEntry::setPosition(Vector2f pos)
{
	LEmove(Vector2f(-m_dimensions.left + pos.x, -m_dimensions.top + pos.y));
}

void LobbyEntry::LEmove(Vector2f delta)
{
	m_nameText.move(delta);
	m_numberText.move(delta);
	move(delta);

	m_dimensions.left += delta.x;
	m_dimensions.top += delta.y;
}

void LobbyEntry::setName(std::string name)
{
	m_nameText.setString(name);
}

std::string LobbyEntry::getName()
{
	return m_nameText.getString();
}

void LobbyEntry::setPlayers(int players)
{
	m_players = players;
	updatePlayers();
}

int LobbyEntry::getPlayers()
{
	return m_players;
}

void LobbyEntry::setMaxPlayers(int maxPlayers)
{
	m_maxPlayers = maxPlayers;
	updatePlayers();
}

int LobbyEntry::getMaxPlayers()
{
	return m_maxPlayers;
}
