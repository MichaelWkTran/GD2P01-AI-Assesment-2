#include "ConsoleInterface.h"
#include "Agent.h"
#include "ExternalVariables.h"
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
	m_pGameManager->Clear();
	m_pGameManager->m_uMaxAgents = 0U;
	m_pGameManager->m_uAgentCount = 0U;
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
		CAgent* Agent = (CAgent*)m_pGameManager->CreateObject<CAgent>();
		Agent->m_AgentBehaviour = AgentBehaviour::Seek;
		
		_RenderWindow.setVisible(true);
		system("CLS");

		std::cout << "Seek\n\n";
		std::cout << "The agent will always move towards your mouse. Move your mouse to change where the agent will move towards.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 1: //Flee
	{
		CAgent* Agent = (CAgent*)m_pGameManager->CreateObject<CAgent>();
		Agent->m_AgentBehaviour = AgentBehaviour::Flee;

		_RenderWindow.setVisible(true);
		system("CLS");

		std::cout << "Flee\n\n";
		std::cout << "The agent will always move away your mouse. Move your mouse to change where the agent will avoid.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 2: //Pursue
	{
		CAgent* Player = (CAgent*)m_pGameManager->CreateObject<CAgent>();
		Player->m_fMaxVelocity = 400.0f;
		Player->m_sprDraw.setColor(sf::Color::Red);
		Player->m_AgentBehaviour = AgentBehaviour::Seek;

		CAgent* Agent = (CAgent*)m_pGameManager->CreateObject<CAgent>();
		Agent->m_pTarget = Player;
		Agent->m_fMaxVelocity = 300.0f;
		Agent->m_AgentBehaviour = AgentBehaviour::Pursue;

		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Pursue\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 3: //Evade
	{
		_RenderWindow.setVisible(true);
		system("CLS");

		CAgent* Player = (CAgent*)m_pGameManager->CreateObject<CAgent>();
		Player->m_fMaxVelocity = 400.0f;
		Player->m_sprDraw.setColor(sf::Color::Red);
		Player->m_AgentBehaviour = AgentBehaviour::Seek;

		CAgent* Agent = (CAgent*)m_pGameManager->CreateObject<CAgent>();
		Agent->m_pTarget = Player;
		Agent->m_fMaxVelocity = 300.0f;
		Agent->m_AgentBehaviour = AgentBehaviour::Evade;

		std::cout << "Evade\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 4: //Wander
	{
		for (int i = 0; i < 30; i++)
		{
			CAgent* Agent = (CAgent*)m_pGameManager->CreateObject<CAgent>();
			Agent->m_fMaxVelocity = 200.0f;
			Agent->m_AgentBehaviour = AgentBehaviour::Wander;
		}
		m_pGameManager->m_uMaxAgents = 50U;
		m_pGameManager->m_uAgentCount = 30U;

		_RenderWindow.setVisible(true);
		system("CLS");

		std::cout << "Wander\n\n";
		std::cout << "All agents will wander around the screen.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 5: //Arrival
	{
		CAgent* Agent = (CAgent*)m_pGameManager->CreateObject<CAgent>();
		Agent->m_AgentBehaviour = AgentBehaviour::Arrival;

		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Arrival\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 6: //Flocking
	{
		_RenderWindow.setVisible(true);
		system("CLS");

		for (int i = 0; i < 30; i++)
		{
			CAgent* Agent = (CAgent*)m_pGameManager->CreateObject<CAgent>();
			Agent->m_fMaxVelocity = 300.0f;
			Agent->m_AgentBehaviour = AgentBehaviour::Flocking;
		}
		m_pGameManager->m_uMaxAgents = 50U;
		m_pGameManager->m_uAgentCount = 30U;

		std::cout << "Flocking\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 7: //Leader Following
	{
		_RenderWindow.setVisible(true);
		system("CLS");

		CAgent* Player = (CAgent*)m_pGameManager->CreateObject<CAgent>();
		Player->m_fMaxVelocity = 100.0f;
		Player->m_sprDraw.setColor(sf::Color::Red);
		Player->m_AgentBehaviour = AgentBehaviour::Seek;

		for (int i = 0; i < 15; i++)
		{
			CAgent* Agent = (CAgent*)m_pGameManager->CreateObject<CAgent>();
			Agent->m_fMaxVelocity = 300.0f;
			Agent->m_pTarget = Player;
			Agent->m_AgentBehaviour = AgentBehaviour::LeaderFollowing;
		}
		m_pGameManager->m_uMaxAgents = 15U;
		m_pGameManager->m_uAgentCount = 15U;

		std::cout << "Leader Following\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 8: //Exit
		m_pGameManager->m_bDeleteObject = true;
		return void();
	}
}