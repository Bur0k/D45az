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

	m_name.setFont(MyFonts::getFont(GameFonts::ARIAL));
	m_name.setString(name);
	m_name.setPosition(m_dimensions.left + LOBBYENTRYBORDER, m_dimensions.top + LOBBYENTRYBORDER);
	
	m_number.setFont(MyFonts::getFont(GameFonts::ARIAL));

	this->setPosition(pos);
	this->setSize(size);
	
}

void LobbyEntry::updatePlayers()
{
	std::string s;
	s = std::to_string(m_players);
	s += " / ";
	s += std::to_string(m_maxPlayers);
	m_name.setString(s);
	sf::Rect<float> textsize = m_name.getLocalBounds();
	m_name.setPosition(m_dimensions.left + m_dimensions.width - textsize.width - LOBBYENTRYBORDER, m_dimensions.top + LOBBYENTRYBORDER);
}

void LobbyEntry::draw(RenderWindow* rw)
{
	rw->draw(m_name);
	rw->draw(m_number);
	rw->draw(*this);
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
	move(Vector2f(m_dimensions.left - pos.x, m_dimensions.top - pos.y));
}

void LobbyEntry::move(Vector2f delta)
{
	m_name.move(delta);
	m_number.move(delta);
	this->move(delta);
}

void LobbyEntry::setName(std::string name)
{
	m_name.setString(name);
}

std::string LobbyEntry::getName()
{
	return m_name.getString();
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
