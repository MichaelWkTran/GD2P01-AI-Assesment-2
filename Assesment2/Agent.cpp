#include "Agent.h"
#include "Vector2Methods.h"
#include <iostream>

CAgent::CAgent()
{
	m_v2fOrigin = sf::Vector2f(16.0f, 16.0f);
	
	m_texDraw.loadFromFile("Assets/Sprites/Agent.png");
	m_sprDraw.setTextureRect(sf::Rect<int>(0, 0, 32, 32));
	m_sprDraw.setColor(sf::Color::Black);

	m_fMass = 1.0f;
	m_fMaxVelocity = 300.0f;
	m_fMaxForce = 300.0f;
}

/*virtual*/ void CAgent::Update(sf::RenderWindow& _RenderWindow, float& _fDeltaTime)
{
	sf::Vector2f v2fMousePosition = _RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(_RenderWindow));

	//Seek
	//{
	//	sf::Vector2f v2fDesiredVelocity = sf::Normalise(v2fMousePosition - m_v2fPosition) * m_fMaxVelocity;
	//	sf::Vector2f v2fSteeringForce = v2fDesiredVelocity - m_v2fVelocity;
	//	v2fSteeringForce = sf::Truncate(v2fSteeringForce, m_fMaxForce);
	//
	//	m_v2fVelocity += (v2fSteeringForce / m_fMass) * _fDeltaTime;
	//	m_v2fVelocity = sf::Truncate(m_v2fVelocity, m_fMaxVelocity);
	//}
	
	//Flee
	//{
	//	sf::Vector2f v2fDesiredVelocity = sf::Normalise(m_v2fPosition - v2fMousePosition) * m_fMaxVelocity;
	//	sf::Vector2f v2fSteeringForce = v2fDesiredVelocity - m_v2fVelocity;
	//	v2fSteeringForce = sf::Truncate(v2fSteeringForce, m_fMaxForce);
	//
	//	m_v2fVelocity += (v2fSteeringForce / m_fMass) * _fDeltaTime;
	//	m_v2fVelocity = sf::Truncate(m_v2fVelocity, m_fMaxVelocity);
	//}

	//Wander
	{

	}

	m_v2fPosition += m_v2fVelocity * _fDeltaTime;
	m_fRotation = (180.0f / 3.141592653589793238463f) * std::atan2f(m_v2fVelocity.y, m_v2fVelocity.x) + 90;
	
	m_sprDraw.setPosition(m_v2fPosition);
	m_sprDraw.setOrigin(m_v2fOrigin);
	m_sprDraw.setScale(m_v2fScale);
	m_sprDraw.setRotation(m_fRotation);

	_RenderWindow.draw(m_sprDraw);
}

void Magnitude()
{

}