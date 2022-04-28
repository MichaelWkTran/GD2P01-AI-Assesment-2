#pragma once
#include <SFML/Graphics.hpp>
#include "Agent.h"

extern sf::Vector2u v2uGameWindowSize;

//Time
extern float fDeltatime;
extern sf::Clock clockDeltaTime;

//Game
extern CAgent* pPlayer;
extern void (*funAgentPropreties)(CAgent*);