#include "GameObject.h"

#pragma once
class CAgent : public CGameObject
{
public:
	float m_fMass;
	sf::Vector2f m_v2fVelocity;
	float m_fMaxVelocity;
	float m_fMaxForce;

	float fWanderTimer;
	float fWanderCooldown;

	sf::Vector2f m_v2fTarget;

	CAgent();

	virtual void Update(sf::RenderWindow& _RenderWindow);
};