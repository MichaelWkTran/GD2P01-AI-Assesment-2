#include "SFML/System/Vector2.hpp"
#include <cmath>

#pragma once
namespace sf
{
	float Magnitude(sf::Vector2f _v2f)
	{
		return std::sqrtf((_v2f.x * _v2f.x) + (_v2f.y * _v2f.y));
	}

	sf::Vector2f Normalise(sf::Vector2f _v2f)
	{
		float&& fMagnitude = Magnitude(_v2f);

		if (fMagnitude != 0) return _v2f / fMagnitude;
		else return sf::Vector2f();
	}

	sf::Vector2f Truncate(sf::Vector2f _v2f, float _fMaxMagnitude)
	{
		if (Magnitude(_v2f) > _fMaxMagnitude) return Normalise(_v2f) * _fMaxMagnitude;
		else return _v2f;
	}
}