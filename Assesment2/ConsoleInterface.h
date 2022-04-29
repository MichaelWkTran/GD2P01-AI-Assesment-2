//This class is used for any interactions involving the console.
//This includes setting up variables and creating objects to be
//used in the game manager when the user chooses a behaviour to view

#pragma once
#include "GameManager.h"

class CConsoleInterface
{
private:
	CGameManager* m_pGameManager;
	
public:
	CConsoleInterface(CGameManager* _pGameManager);

	void Update(sf::RenderWindow& _RenderWindow);
};