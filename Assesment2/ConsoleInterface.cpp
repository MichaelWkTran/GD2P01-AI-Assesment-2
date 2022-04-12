#include "ConsoleInterface.h"
//#include "GameManager.h"
//#include <iostream>
//#include <limits>

CConsoleInterface::CConsoleInterface(CGameManager* _pGameManager)
{
	m_pGameManager = _pGameManager;
}

void CConsoleInterface::Update(sf::RenderWindow& _RenderWindow)
{
	_RenderWindow.setVisible(false);
	int iInput = -1;

	while (true)
	{
		system("CLS");

		std::cout << "0) Seek\n";
		std::cout << "1) Flee\n";
		std::cout << "2) Pursue\n";
		std::cout << "3) Evade\n";
		std::cout << "4) Wander\n";
		std::cout << "5) Arrival\n";

		std::cout << "\nCombined Behaviours\n";
		std::cout << "6) Flocking\n";
		std::cout << "7) Leader Following\n\n";

		std::cout << "8) Exit\n\n\n";

		std::cout << "Type the number corresponding to the option you want to choose above and press ENTER to confirm\n";
		
		try 
		{
			std::cin >> iInput;
			if (std::cin.fail() || (iInput < 0 || iInput > 8)) throw -1;
		}
		catch (...)
		{
			iInput = -1;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "ERROR: Input Invalid. Your input must be an integer that is from 0 to 7\n";
			system("pause");
			continue;
		}

		break;
	}

	switch (iInput)
	{
	case 0: //Seek
	{
		m_pGameManager->m_GameState = GameState::Seek;
		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Seek\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 1: //Flee
	{
		m_pGameManager->m_GameState = GameState::Flee;
		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Flee\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 2: //Pursue
	{
		m_pGameManager->m_GameState = GameState::Pursue;
		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Pursue\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 3: //Evade
	{
		m_pGameManager->m_GameState = GameState::Evade;
		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Evade\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 4: //Wander
	{
		m_pGameManager->m_GameState = GameState::Wander;
		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Wander\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 5: //Arrival
	{
		m_pGameManager->m_GameState = GameState::Arrival;
		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Arrival\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 6: //Flocking
	{
		m_pGameManager->m_GameState = GameState::Flocking;
		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Flocking\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 7: //Leader Following
	{
		m_pGameManager->m_GameState = GameState::LeaderFollowing;
		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Leader Following\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 8: //Exit
		m_pGameManager->m_bDeleteObject = true;
		return void();
	}
}