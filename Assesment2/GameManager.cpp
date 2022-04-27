#include "GameManager.h"
//#include <SFML/Graphics.hpp>
//#include <string>
#include "Agent.h"

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
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		//{
		//	if (!m_bLeftMouseButtonPressed)
		//	{
		//		m_bLeftMouseButtonPressed = true;
		//
		//		//Create Agent
		//		if (m_uAgentCount < m_uMaxAgents)
		//		{
		//			CreateObject<CAgent*>();
		//			m_uAgentCount++;
		//		}
		//	}
		//}
		//else
		//{
		//	if (m_bLeftMouseButtonPressed) m_bLeftMouseButtonPressed = false;
		//}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			if (!m_bRightMouseButtonPressed)
			{
				m_bRightMouseButtonPressed = true;

				//Delete Agents
				if (m_uAgentCount > 0)
				{
					for (CUpdatedObject*& pUpdatedObjects : m_dequeUpdatedObjects)
						if (dynamic_cast<CAgent*>(pUpdatedObjects) != nullptr)
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
			if (m_bRightMouseButtonPressed) m_bRightMouseButtonPressed = false;
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