#pragma once
#include "GameObject.h"
#include "GameManager.h"

enum class AgentBehaviour { Seek, Flee, Pursue, Evade, Wander, Arrival, Flocking, LeaderFollowing };

class CAgent : public CGameObject
{
public:
	AgentBehaviour m_AgentBehaviour;

	float m_fMass;
	sf::Vector2f m_v2fVelocity;
	float m_fMaxVelocity;
	float m_fMaxForce;

	float m_fWanderTimer;
	float m_fWanderCooldown;
	sf::Vector2f m_v2fWanderTarget;
	CAgent* m_pTarget;

	CAgent();
	virtual ~CAgent();

	virtual void Update(sf::RenderWindow& _RenderWindow);
};