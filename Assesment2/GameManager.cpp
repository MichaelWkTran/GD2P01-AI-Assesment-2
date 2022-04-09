#include "GameManager.h"
//#include <SFML/Graphics.hpp>
//#include <string>

CGameManager::CGameManager()
{
	m_GameState = GameState::Seek;
	m_bDeleteGameManager = false;

	//UI Variables
	m_fntCurrent.loadFromFile("Assets/Fonts/arial.ttf");
	m_txtCurrent.setFont(m_fntCurrent); m_txtCurrent.setCharacterSize(20U);
}

void CGameManager::DeleteGameManager()
{
	m_bDeleteGameManager = true;
}

bool CGameManager::GetDeleteGameManager() const
{
	return m_bDeleteGameManager;
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

}