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

void CGameManager::Update(sf::RenderWindow& _RenderWindow, float& _fDeltaTime)
{
	//Delete objects in m_dequeUpdatedObject
	for (unsigned uObjectIndex = 0; uObjectIndex < m_dequeUpdatedObject.size(); uObjectIndex++)
		if (m_dequeUpdatedObject[uObjectIndex].m_bDeleteObject) m_dequeUpdatedObject.erase(m_dequeUpdatedObject.begin() + uObjectIndex);
}