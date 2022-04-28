#include "ExternalVariables.h"
//#include <SFML/Graphics.hpp>
//#include "Agent.h"

sf::Vector2u v2uGameWindowSize(800U, 450U);

//Time
float fDeltatime = 0.0f;
sf::Clock clockDeltaTime;

//Game
CAgent* pPlayer = nullptr;
extern void (*funAgentPropreties)(CAgent*) = nullptr;