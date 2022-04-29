#include "ConsoleInterface.h"
#include "ExternalVariables.h"
#include "Agent.h"
#include <iostream>

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
	e_pPlayer = nullptr;
	e_funAgentPropreties = nullptr;
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
		CAgent* pAgent = m_pGameManager->CreateObject<CAgent>();
		pAgent->m_AgentBehaviour = AgentBehaviour::Seek;
		
		_RenderWindow.setVisible(true);
		system("CLS");

		std::cout << "Seek\n\n";
		std::cout << "The agent will always move towards your mouse. Move your mouse to change where the agent will move towards.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 1: //Flee
	{
		CAgent* pAgent = m_pGameManager->CreateObject<CAgent>();
		pAgent->m_AgentBehaviour = AgentBehaviour::Flee;

		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Flee\n\n";
		std::cout << "The agent will always move away your mouse. Move your mouse to change where the agent will avoid.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 2: //Pursue
	{
		e_pPlayer = m_pGameManager->CreateObject<CAgent>();
		e_pPlayer->m_fMaxVelocity = 400.0f;
		e_pPlayer->m_sprDraw.setColor(sf::Color::Red);
		e_pPlayer->m_AgentBehaviour = AgentBehaviour::Seek;

		CAgent* pAgent = m_pGameManager->CreateObject<CAgent>();
		pAgent->m_pTarget = e_pPlayer;
		pAgent->m_fMaxVelocity = 300.0f;
		pAgent->m_AgentBehaviour = AgentBehaviour::Pursue;

		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Pursue\n\n";
		std::cout << "The agent will approach the point the player is heading.\n";
		std::cout << "The player is the red arrow that follows your mouse. Move your mouse to change where the player will move towards.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 3: //Evade
	{
		_RenderWindow.setVisible(true);
		system("CLS");

		e_pPlayer = m_pGameManager->CreateObject<CAgent>();
		e_pPlayer->m_fMaxVelocity = 400.0f;
		e_pPlayer->m_sprDraw.setColor(sf::Color::Red);
		e_pPlayer->m_AgentBehaviour = AgentBehaviour::Seek;

		CAgent* pAgent = m_pGameManager->CreateObject<CAgent>();
		pAgent->m_pTarget = e_pPlayer;
		pAgent->m_fMaxVelocity = 300.0f;
		pAgent->m_AgentBehaviour = AgentBehaviour::Evade;


		std::cout << "Evade\n\n";
		std::cout << "The agent will avoid the point the player is heading.\n";
		std::cout << "The player is the red arrow that follows your mouse. Move your mouse to change where the player will move towards.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 4: //Wander
	{
		e_funAgentPropreties = [](CAgent* _pAgent) -> void
		{
			_pAgent->m_fMaxVelocity = 200.0f;
			_pAgent->m_AgentBehaviour = AgentBehaviour::Wander;
		};

		for (int i = 0; i < 30; i++) e_funAgentPropreties(m_pGameManager->CreateObject<CAgent>());
		
		m_pGameManager->m_uMaxAgents = 50U;
		m_pGameManager->m_uAgentCount = 30U;

		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Wander\n\n";
		std::cout << "All agents will wander around the screen.\n";
		std::cout << "Press the left mouse button to create an agent and press the right mouse button to delete one.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 5: //Arrival
	{
		CAgent* pAgent = m_pGameManager->CreateObject<CAgent>();
		pAgent->m_AgentBehaviour = AgentBehaviour::Arrival;

		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Arrival\n\n";
		std::cout << "The agent will approach the mouse and slow down until it stops at it. Move your mouse to change where the agent will avoid.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 6: //Flocking
	{
		e_funAgentPropreties = [](CAgent* _pAgent) -> void
		{
			_pAgent->m_fMaxVelocity = 200.0f;
			_pAgent->m_AgentBehaviour = AgentBehaviour::Flocking;
		};
		
		for (int i = 0; i < 30; i++) e_funAgentPropreties(m_pGameManager->CreateObject<CAgent>());
		
		m_pGameManager->m_uMaxAgents = 50U;
		m_pGameManager->m_uAgentCount = 30U;

		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Flocking\n\n";
		std::cout << "All agents will group together and follow a common direction. \n";
		std::cout << "Press the left mouse button to create an agent and press the right mouse button to delete one.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 7: //Leader Following
	{
		e_pPlayer = m_pGameManager->CreateObject<CAgent>();
		e_pPlayer->m_fMaxVelocity = 50.0f;
		e_pPlayer->m_sprDraw.setColor(sf::Color::Red);
		e_pPlayer->m_AgentBehaviour = AgentBehaviour::Seek;

		e_funAgentPropreties = [](CAgent* _pAgent) -> void
		{
			_pAgent->m_fMaxVelocity = 150.0f;
			_pAgent->m_pTarget = e_pPlayer;
			_pAgent->m_AgentBehaviour = AgentBehaviour::LeaderFollowing;
		};

		for (int i = 0; i < 15; i++) e_funAgentPropreties(m_pGameManager->CreateObject<CAgent>());

		m_pGameManager->m_uMaxAgents = 15U;
		m_pGameManager->m_uAgentCount = 15U;

		_RenderWindow.setVisible(true);
		system("CLS");


		std::cout << "Leader Following\n\n";
		std::cout << "All agents will group together and follow behind the player. \n";
		std::cout << "Press the left mouse button to create an agent and press the right mouse button to delete one.\n\n";
		std::cout << "Press BACKSPACE to return to the main menu";


		return void();
	}
	case 8: //Exit
		m_pGameManager->m_bDeleteObject = true;
		return void();
	}
}