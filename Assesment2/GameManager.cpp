#include "GameManager.h"
#include "Agent.h"
#include "ExternalVariables.h"
#include <iostream>

CGameManager::CGameManager()
{
	m_bLeftMouseButtonPressed = false;
	m_bRightMouseButtonPressed = false;
	m_uMaxAgents = 0U;
	m_uAgentCount = 0U;
}

void CGameManager::Clear()
{
	for (CUpdatedObject*& pUpdatedObjects : m_dequeUpdatedObjects)
	{
		if (pUpdatedObjects != nullptr) delete pUpdatedObjects;
		pUpdatedObjects = nullptr;
	}

	m_dequeUpdatedObjects.clear();
}

sf::Vector2f* CGameManager::GetViewPositionPointer()
{
	return &m_v2fViewPosition;
}

void CGameManager::SetViewPosition(const sf::Vector2f _v2fViewPosition)
{
	m_v2fViewPosition = _v2fViewPosition;
}

void CGameManager::Update(sf::RenderWindow& _RenderWindow)
{
	//When m_uMaxAgents == 0, deleting and creating agents are disabled
	if (m_uMaxAgents > 0)
	{
		//Check Mouse Input and Create or delete Agents
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			//When the left mouse button is held

			if (!m_bLeftMouseButtonPressed)
			{
				//When the left mouse button is pressed
				m_bLeftMouseButtonPressed = true;
		
				//Create Agent
				if (m_uAgentCount < m_uMaxAgents)
				{
					CAgent* pAgent = CreateObject<CAgent>();
					e_funAgentPropreties(pAgent);
					pAgent->m_v2fPosition = _RenderWindow.mapPixelToCoords(sf::Mouse::getPosition(_RenderWindow));

					m_uAgentCount++;
				}
			}
		}
		else
		{
			if (m_bLeftMouseButtonPressed)
			{
				//When the left mouse button is released
				m_bLeftMouseButtonPressed = false;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			//When the right mouse button is held

			if (!m_bRightMouseButtonPressed)
			{
				//When the right mouse button is pressed
				m_bRightMouseButtonPressed = true;

				//Delete Agents
				if (m_uAgentCount > 0)
				{
					for (CUpdatedObject*& pUpdatedObjects : m_dequeUpdatedObjects)
						if (dynamic_cast<CAgent*>(pUpdatedObjects) != nullptr && dynamic_cast<CAgent*>(pUpdatedObjects) != e_pPlayer)
						{
							pUpdatedObjects->m_bDeleteObject = true;
							m_uAgentCount--;
							break;
						}
				}
			}
		}
		else
		{
			if (m_bRightMouseButtonPressed)
			{
				//When the right mouse button is released
				m_bRightMouseButtonPressed = false;
			}
		}
	}

	//Delete objects in m_dequeUpdatedObject
	for (unsigned uObjectIndex = 0; uObjectIndex < m_dequeUpdatedObjects.size(); uObjectIndex++)
		if (m_dequeUpdatedObjects[uObjectIndex]->m_bDeleteObject)
		{
			delete m_dequeUpdatedObjects[uObjectIndex];
			m_dequeUpdatedObjects[uObjectIndex] = nullptr;
			m_dequeUpdatedObjects.erase(m_dequeUpdatedObjects.begin() + uObjectIndex);
		}

	//Update remaining objects
	for (CUpdatedObject* pUpdatedObject : m_dequeUpdatedObjects)
	{
		pUpdatedObject->Update(_RenderWindow);
	}
}