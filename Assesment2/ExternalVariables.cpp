#include "ExternalVariables.h"

sf::Vector2u e_v2uGameWindowSize(800U, 450U);

//Time
float e_fDeltatime = 0.0f;
sf::Clock e_clockDeltaTime;

//Game
CAgent* e_pPlayer = nullptr;
void (*e_funAgentPropreties)(CAgent*) = nullptr;