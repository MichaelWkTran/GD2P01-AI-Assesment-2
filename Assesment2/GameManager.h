#include <SFML/Graphics.hpp>
#include <string>
#include <deque>
#include <functional>
#include "UpdatedObject.h"
#include <iostream>

#pragma once
class CGameManager : public CUpdatedObject
{
private:
	//Game Variables
	sf::Vector2f m_v2fViewPosition;
	bool m_bLeftMouseButtonPressed;
	bool m_bRightMouseButtonPressed;

public:
	std::deque<CUpdatedObject*> m_dequeUpdatedObjects;
	unsigned int m_uMaxAgents;
	unsigned int m_uAgentCount;

	CGameManager();
	~CGameManager() {};

	template <class T>
	/*inline*/ T* CreateObject();
	void Clear();

	sf::Vector2f* GetViewPositionPointer();
	void SetViewPosition(const sf::Vector2f _v2fViewPosition);
	void Update(sf::RenderWindow& _RenderWindow);
};

template<class T>
inline T* CGameManager::CreateObject()
{
	m_dequeUpdatedObjects.emplace_back(new T);
	m_dequeUpdatedObjects.back()->m_pManager = this;
	return (T*)m_dequeUpdatedObjects.back();
}
