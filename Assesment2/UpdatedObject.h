#include <SFML/Graphics.hpp>

#pragma once
class CUpdatedObject
{
public:
	bool m_bDeleteObject = false;
	virtual void Update(sf::RenderWindow& _RenderWindow) = 0;
};