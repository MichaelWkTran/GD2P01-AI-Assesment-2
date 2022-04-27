#include "Agent.h"
#include "Vector2Methods.h"
#include <iostream>
#include "ExternalVariables.h"
#include "SteeringBehaviors.h"
#include "GameManager.h"

CAgent::CAgent()
{
	m_v2fPosition = sf::Vector2f(v2uGameWindowSize) / 2.0f;
	m_v2fOrigin = sf::Vector2f(16.0f, 16.0f);
	
	m_texDraw.loadFromFile("Assets/Sprites/Agent.png");
	m_sprDraw.setTextureRect(sf::Rect<int>(0, 0, 32, 32));
	m_sprDraw.setColor(sf::Color::Black);

	m_AgentBehaviour = AgentBehaviour::Seek;

	m_fMass = 1.0f;
	m_fMaxVelocity = 600.0f;
	m_fMaxForce = 300.0f;

	fWanderTimer = 0.5f;
	fWanderCooldown = 0.0f;
	m_pTarget = nullptr;
}

CAgent::~CAgent()
{
	m_pTarget = nullptr;
}

/*virtual*/ void CAgent::Update(sf::RenderWindow& _RenderWindow)
{
	auto AddForce = [this](sf::Vector2f&& _v2fForce) -> void
	{
		SteeringBehaviours::AddForce(_v2fForce, m_v2fVelocity, m_fMaxVelocity, m_fMaxForce);
	};

	switch (m_AgentBehaviour)
	{
	case AgentBehaviour::Seek:
	{
		sf::Vector2f v2fTarget = _RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(_RenderWindow));
		AddForce(SteeringBehaviours::Seek(m_v2fPosition, v2fTarget, m_v2fVelocity, m_fMaxVelocity));

		break;
	}
	case AgentBehaviour::Flee:
	{
		sf::Vector2f v2fTarget = _RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(_RenderWindow));
		AddForce(SteeringBehaviours::Flee(m_v2fPosition, v2fTarget, m_v2fVelocity, m_fMaxVelocity));

		break;
	}
	case AgentBehaviour::Pursue:
	{
		if (m_pTarget == nullptr) break;
	
		sf::Vector2f v2fTarget = SteeringBehaviours::GetPursueTargetPosition(m_v2fPosition, m_pTarget->m_v2fPosition, m_v2fVelocity, m_pTarget->m_v2fVelocity, 10000.0f);
		AddForce(SteeringBehaviours::Seek(m_v2fPosition, v2fTarget, m_v2fVelocity, m_fMaxVelocity));

		break;
	}	
	case AgentBehaviour::Evade:
	{
		if (m_pTarget == nullptr) break;
	
		sf::Vector2f v2fTarget = SteeringBehaviours::GetPursueTargetPosition(m_v2fPosition, m_pTarget->m_v2fPosition, m_v2fVelocity, m_pTarget->m_v2fVelocity, 10000.0f);
		AddForce(SteeringBehaviours::Flee(m_v2fPosition, v2fTarget, m_v2fVelocity, m_fMaxVelocity));

		break;
	}
	case AgentBehaviour::Wander:
	{
		if (fWanderCooldown <= 0)
		{
			m_v2fWanderTarget = SteeringBehaviours::GetWanderTargetPosition(150.0f, 80.0f, m_v2fPosition, m_v2fVelocity);
			fWanderCooldown = fWanderTimer;
		}
		else
		{
			fWanderCooldown -= fDeltatime;
		}
	
		AddForce(SteeringBehaviours::Seek(m_v2fPosition, m_v2fWanderTarget, m_v2fVelocity, m_fMaxVelocity));

		break;
	}
	case AgentBehaviour::Arrival:
	{
		sf::Vector2f v2fTarget = _RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(_RenderWindow));
		AddForce(SteeringBehaviours::Arrive(400.0f, m_v2fPosition, v2fTarget, m_v2fVelocity, m_fMaxVelocity));

		break;
	}
	case AgentBehaviour::Flocking:
	{
		CGameManager* m_pGameManager = (CGameManager*)m_pManager;

		//Variables
		float fCohesionRadius = 400;
		std::vector<sf::Vector2f> vCohesionNeighbours;
		std::vector<sf::Vector2f> vCohesionNeighbourVelocities;
		
		float fSepparationRadius = 200;
		std::vector<sf::Vector2f> vSepparationNeighbours;

		//Find agents within cohesion && sepparation radius
		for (CUpdatedObject* pNeighbour : m_pGameManager->m_dequeUpdatedObjects)
		{
			if (dynamic_cast<CAgent*>(pNeighbour) == 0) continue;

			CAgent* pNeighbourAgent = (CAgent*)pNeighbour;
			if (pNeighbourAgent == this) continue;

			float fDistance = Magnitude(m_v2fPosition - pNeighbourAgent->m_v2fPosition);
			if (fDistance < fCohesionRadius)
			{
				vCohesionNeighbours.push_back(pNeighbourAgent->m_v2fPosition);
				vCohesionNeighbourVelocities.push_back(pNeighbourAgent->m_v2fVelocity);

				if (fDistance < fSepparationRadius) vSepparationNeighbours.push_back(pNeighbourAgent->m_v2fPosition);
			}
		}

		sf::Vector2f v2fSteeringForce;
		v2fSteeringForce += SteeringBehaviours::Separation(fSepparationRadius, vSepparationNeighbours, m_v2fPosition, m_v2fVelocity, m_fMaxVelocity) * 0.6f;
		v2fSteeringForce += SteeringBehaviours::Alignment(vCohesionNeighbours, vCohesionNeighbourVelocities, m_v2fVelocity) * 0.15f;
		sf::Vector2f v2fTarget = SteeringBehaviours::GetCohesionCentreOfMass(vCohesionNeighbours, m_v2fPosition);
		v2fSteeringForce += SteeringBehaviours::Seek(m_v2fPosition, v2fTarget, m_v2fVelocity, m_fMaxVelocity) * 0.25f;

		AddForce(std::move(v2fSteeringForce));
		//AddForce(SteeringBehaviours::Separation(fSepparationRadius, vSepparationNeighbours, m_v2fPosition, m_v2fVelocity, m_fMaxVelocity));
		break;
	}
	case AgentBehaviour::LeaderFollowing:
	{
		if (m_pTarget == nullptr) break;

		CGameManager* m_pGameManager = (CGameManager*)m_pManager;
		sf::Vector2f v2fTarget;
		sf::Vector2f v2fSteeringForce;

		//Check whether in front of the leader
		bool bInfrontOfLeader = false;
		{
			float fLeaderConeRadius = 200.0f;
			float fLeaderConeAngle = 30.0f * (3.141592653589793238463f / 180.0f);

			if (sf::Magnitude(m_pTarget->m_v2fPosition - m_v2fPosition) < fLeaderConeRadius)
			{
				sf::Vector2f v2fTargetVelocityNormal = sf::Normalise(m_pTarget->m_v2fVelocity);
				sf::Vector2f v2fTargetOffsetNormal = sf::Normalise(m_v2fPosition - m_pTarget->m_v2fPosition);

				float fDotProduct = (v2fTargetVelocityNormal.x * v2fTargetOffsetNormal.x) + (v2fTargetVelocityNormal.y * v2fTargetOffsetNormal.y);
				float fDotProductAngle = fabsf( std::acosf(fDotProduct) );

				if (fDotProductAngle < fLeaderConeAngle)
				{
					bInfrontOfLeader = true;
				}
			}
		}

		//Apply forces
		if (bInfrontOfLeader)
		{
			//Apply Evade Force
			float fMaxPrediction = 80.0f;
			v2fTarget = SteeringBehaviours::GetPursueTargetPosition(m_v2fPosition, m_pTarget->m_v2fPosition, m_v2fVelocity, m_pTarget->m_v2fVelocity, 10000.0f);
			v2fSteeringForce = SteeringBehaviours::Flee(m_v2fPosition, v2fTarget, m_v2fVelocity, m_fMaxVelocity);
		}
		else
		{
			float fSepparationRadius = 50;
			
			//Find agents within Sepparation radius
			std::vector<sf::Vector2f> vSepparationNeighbours;
			for (CUpdatedObject* pNeighbour : m_pGameManager->m_dequeUpdatedObjects)
			{
				if (dynamic_cast<CAgent*>(pNeighbour) == 0) continue;

				CAgent* pNeighbourAgent = (CAgent*)pNeighbour;
				if (pNeighbourAgent == this) continue;

				float fDistance = Magnitude(m_v2fPosition - pNeighbourAgent->m_v2fPosition);
				if (fDistance < fSepparationRadius) vSepparationNeighbours.push_back(pNeighbourAgent->m_v2fPosition);
			}

			//Apply Sepparation Force
			v2fSteeringForce += SteeringBehaviours::Separation(fSepparationRadius, vSepparationNeighbours, m_v2fPosition, m_v2fVelocity, m_fMaxVelocity) * 0.6f;

			//Apply ArriveForce
			float fLeaderBehindDistance = 100.0f;
			v2fTarget = m_pTarget->m_v2fPosition - (sf::Normalise(m_pTarget->m_v2fVelocity) * fLeaderBehindDistance);
			v2fSteeringForce += SteeringBehaviours::Arrive(400.0f, m_v2fPosition, v2fTarget, m_v2fVelocity, m_fMaxVelocity) * 0.4f;
		}


		AddForce(std::move(v2fSteeringForce));

		break;
	}
	}
	
	//Screen Wrap
	{
		auto MomemtumOutsideBounds = [this]()
		{
			if (sf::Magnitude(m_v2fVelocity) < 300.0f && (m_AgentBehaviour == AgentBehaviour::Flee || m_AgentBehaviour == AgentBehaviour::Evade)) { m_v2fVelocity = sf::Normalise(m_v2fVelocity) * 300.0f; }
		};

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