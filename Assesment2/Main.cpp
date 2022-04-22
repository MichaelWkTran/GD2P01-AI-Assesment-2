#include "ExternalVariables.h"
#include <SFML/Graphics.hpp>
#include "ConsoleInterface.h"
#include "GameManager.h"
#include "Agent.h"
#include "Button.h"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

void SetView(sf::RenderWindow& GameWindow, sf::View& GameWindowView, const sf::Vector2u& _v2uOriginalSize);

int main()
{
	//Create Game Manager
	CGameManager* pGameManager = new CGameManager();

	//Create Console Interace
	CConsoleInterface ConsoleInterface(pGameManager);
	
	//Create the game window
	sf::RenderWindow GameWindow(sf::VideoMode(v2uGameWindowSize.x, v2uGameWindowSize.y), "");
	sf::View GameWindowView;

	srand((unsigned int)time(NULL));

	//Open Console Interface
	ConsoleInterface.Update(GameWindow);
	
	//Update Game Window
	while (GameWindow.isOpen())
	{
		//Set Delta Time
		fDeltatime = clockDeltaTime.restart().asSeconds();
		
		//Poll Events
		sf::Event WindowEvent;
		while (GameWindow.pollEvent(WindowEvent))
		{
			switch (WindowEvent.type)
			{
			case sf::Event::KeyPressed:
				if (WindowEvent.key.code == sf::Keyboard::BackSpace) { ConsoleInterface.Update(GameWindow); }
				break;
			case sf::Event::Closed:
				ConsoleInterface.Update(GameWindow);
				break;
			case sf::Event::Resized:
				SetView(GameWindow, GameWindowView, v2uGameWindowSize);
				break;
			}
		}
		
		//Check whether the Game Manager should be deleted
		if (pGameManager != nullptr && pGameManager->m_bDeleteObject)
		{
			delete pGameManager; pGameManager = nullptr;
		}

		//Game loop
		if (pGameManager != nullptr) 
		{
			GameWindow.clear(sf::Color(255U,255U,255U));

			if (GameWindow.hasFocus()) pGameManager->Update(GameWindow);

			GameWindow.display();
		}
		else
		{
			GameWindow.close();
		}
	}
}

void SetView(sf::RenderWindow& _RenderWindow, sf::View& _View, const sf::Vector2u& _v2uOriginalSize)
{
	//Maintain the aespect ratio of the window when resized
	sf::Rect<float> VisibleArea;

	float fViewAespectRatio = ((float)_v2uOriginalSize.x) / ((float)_v2uOriginalSize.y);

	float NewViewWidth = fViewAespectRatio * _RenderWindow.getSize().y;
	float NewViewHeight = _RenderWindow.getSize().x / fViewAespectRatio;

	float fViewOffsetX = (_RenderWindow.getSize().x - NewViewWidth) / 2.0f;
	float fViewOffsetY = (_RenderWindow.getSize().y - NewViewHeight) / 2.0f;

	_View = _RenderWindow.getDefaultView();

	if (_RenderWindow.getSize().x >= fViewAespectRatio * _RenderWindow.getSize().y)
	{
		_View.setViewport
		(
			sf::FloatRect
			(
				fViewOffsetX / _RenderWindow.getSize().x,
				0.0f,
				NewViewWidth / _RenderWindow.getSize().x,
				1.0f
			)
		);
	}
	else
	{
		_View.setViewport
		(
			sf::FloatRect
			(
				0.0f,
				fViewOffsetY / _RenderWindow.getSize().y,
				1.0f,
				NewViewHeight / _RenderWindow.getSize().y
			)
		);
	}

	_RenderWindow.setView(_View);
}