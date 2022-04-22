#include "GameManager.h"
//#include <SFML/Graphics.hpp>
//#include <string>

CGameManager::CGameManager()
{
	m_GameState = GameState::Seek;

	//UI Variables
	m_fntCurrent.loadFromFile("Assets/Fonts/arial.ttf");
	m_txtCurrent.setFont(m_fntCurrent); m_txtCurrent.setCharacterSize(20U);
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
	//Delete objects in m_dequeUpdatedObject
	for (unsigned uObjectIndex = 0; uObjectIndex < m_dequeUpdatedObjects.size(); uObjectIndex++)
		if (m_dequeUpdatedObjects[uObjectIndex]->m_bDeleteObject)
		{
			delete m_dequeUpdatedObjects[uObjectIndex];
			m_dequeUpdatedObjects.erase(m_dequeUpdatedObjects.begin() + uObjectIndex);
		}

	for (CUpdatedObject* pUpdatedObject : m_dequeUpdatedObjects)
	{
		pUpdatedObject->Update(_RenderWindow);
	}
}