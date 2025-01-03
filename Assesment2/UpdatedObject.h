#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class CUpdatedObject
{
public:
	CUpdatedObject* m_pManager = nullptr;
	bool m_bDeleteObject = false;
	
	virtual ~CUpdatedObject() { m_pManager = nullptr; };
	virtual void Update(sf::RenderWindow& _RenderWindow) = 0;
};