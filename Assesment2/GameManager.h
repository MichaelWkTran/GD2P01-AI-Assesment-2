#include <SFML/Graphics.hpp>
#include <string>
#include <deque>
#include <functional>
#include "UpdatedObject.h"

#pragma once
enum class GameState {Seek, Flee, Pursue, Evade, Wander, Arrival, Flocking, LeaderFollowing};

class CGameManager : public CUpdatedObject
{
private:
	//Game Variables
	std::deque<CUpdatedObject> m_dequeUpdatedObject;
	sf::Vector2f m_v2fViewPosition;
	
	//UI Variables
	sf::Font m_fntCurrent;
	sf::Text m_txtCurrent;

public:
	GameState m_GameState;

	CGameManager();

	sf::Vector2f* GetViewPositionPointer();
	void SetViewPosition(const sf::Vector2f _v2fViewPosition);
	void Update(sf::RenderWindow& _RenderWindow, float& _fDeltaTime);
};