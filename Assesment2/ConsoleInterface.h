#include "GameManager.h"
#include <iostream>
#include <limits>

#pragma once
class CConsoleInterface
{
private:
	CGameManager* m_pGameManager;
	
public:
	CConsoleInterface(CGameManager* _pGameManager);

	void Update(sf::RenderWindow& _RenderWindow);
};