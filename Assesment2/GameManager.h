#include <SFML/Graphics.hpp>
#include <string>

#pragma once
enum class GameState {Seek, Flee, Pursue, Evade, Wander, Arrival, Flocking, LeaderFollowing};

class CGameManager
{
private:
	bool m_bDeleteGameManager;

	//Game Variables
	sf::Vector2f m_v2fViewPosition;

	//UI Variables
	sf::Font m_fntCurrent;
	sf::Text m_txtCurrent;

public:
	GameState m_GameState;

	CGameManager();

	void DeleteGameManager();
	bool GetDeleteGameManager() const;
	
	sf::Vector2f* GetViewPositionPointer();
	void SetViewPosition(const sf::Vector2f _v2fViewPosition);
	void Update(sf::RenderWindow& _RenderWindow, float& _fDeltaTime);
};