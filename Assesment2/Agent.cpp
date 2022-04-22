#include "Agent.h"
#include "Vector2Methods.h"
#include <iostream>
#include "ExternalVariables.h"
#include "SteeringBehaviors.h"

CAgent::CAgent()
{
	m_v2fPosition = sf::Vector2f(v2uGameWindowSize) / 2.0f;
	m_v2fOrigin = sf::Vector2f(16.0f, 16.0f);
	
	m_texDraw.loadFromFile("Assets/Sprites/Agent.png");
	m_sprDraw.setTextureRect(sf::Rect<int>(0, 0, 32, 32));
	m_sprDraw.setColor(sf::Color::Black);

	m_fMass = 1.0f;
	m_fMaxVelocity = 200.0f;//600.0f;
	m_fMaxForce = 300.0f;

	fWanderTimer = 0.2f;
	fWanderCooldown = 0.0f;
}

/*virtual*/ void CAgent::Update(sf::RenderWindow& _RenderWindow)
{
	//m_v2fTarget = _RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(_RenderWindow));

	if (fWanderCooldown <= 0)
	{
		m_v2fTarget = SteeringBehaviours::GetWanderTargetPosition(m_v2fPosition, 100.0f, 80.0f, m_v2fVelocity, m_fMaxVelocity, m_fMaxForce, m_fMass);
		fWanderCooldown = fWanderTimer;
	}
	else
	{
		fWanderCooldown -= fDeltatime;
	}
	
	SteeringBehaviours::SeekFlee(m_v2fPosition, m_v2fTarget, m_v2fVelocity, m_fMaxVelocity, m_fMaxForce);
	
	//Screen Wrap
	{
		auto MomemtumOutsideBounds = [this]() {};//if (sf::Magnitude(m_v2fVelocity) < 300.0f) { m_v2fVelocity = sf::Normalise(m_v2fVelocity) * 300.0f; } };

		if (m_v2fPosition.x < -m_sprDraw.getTextureRect().width) { m_v2fPosition.x = (float)v2uGameWindowSize.x + (float)m_sprDraw.getTextureRect().width; MomemtumOutsideBounds(); }
		else if (m_v2fPosition.x > (float)v2uGameWindowSize.x + m_sprDraw.getTextureRect().width) { m_v2fPosition.x = -(float)m_sprDraw.getTextureRect().width; MomemtumOutsideBounds(); }

		if (m_v2fPosition.y < -m_sprDraw.getTextureRect().height) { m_v2fPosition.y = (float)v2uGameWindowSize.y + (float)m_sprDraw.getTextureRect().height; MomemtumOutsideBounds(); }
		else if (m_v2fPosition.y > (float)v2uGameWindowSize.y + m_sprDraw.getTextureRect().height) { m_v2fPosition.y = -(float)m_sprDraw.getTextureRect().height; MomemtumOutsideBounds(); }
	}
	
	m_v2fPosition += m_v2fVelocity * fDeltatime;
	m_fRotation = (180.0f / 3.141592653589793238463f) * std::atan2f(m_v2fVelocity.y, m_v2fVelocity.x) + 90.0f;

	m_sprDraw.setPosition(m_v2fPosition);
	m_sprDraw.setOrigin(m_v2fOrigin);
	m_sprDraw.setScale(m_v2fScale);
	m_sprDraw.setRotation(m_fRotation);

	_RenderWindow.draw(m_sprDraw);
}