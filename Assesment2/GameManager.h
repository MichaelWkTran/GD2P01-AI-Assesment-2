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
	
	//UI Variables
	sf::Font m_fntCurrent;
	sf::Text m_txtCurrent;

public:
	std::deque<CUpdatedObject*> m_dequeUpdatedObjects;

	CGameManager();

	template <class T>
	/*inline*/ CUpdatedObject* CreateObject();
	void Clear();

	sf::Vector2f* GetViewPositionPointer();
	void SetViewPosition(const sf::Vector2f _v2fViewPosition);
	void Update(sf::RenderWindow& _RenderWindow);
};

template<class T>
inline CUpdatedObject* CGameManager::CreateObject()
{
	m_dequeUpdatedObjects.push_back(new T);
	return m_dequeUpdatedObjects.back();
}
