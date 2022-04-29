#pragma once
#include <SFML/Graphics.hpp>
#include "Agent.h"

extern sf::Vector2u e_v2uGameWindowSize;

//Time
extern float e_fDeltatime;
extern sf::Clock e_clockDeltaTime;

//Game
extern CAgent* e_pPlayer;
extern void (*e_funAgentPropreties)(CAgent*);