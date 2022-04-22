#pragma once
#include "SFML/System/Vector2.hpp"
#include "Vector2Methods.h"
#include "ExternalVariables.h"
#include <stdlib.h>
#include <time.h>

using namespace sf;

namespace SteeringBehaviours
{
	void SeekFlee(Vector2f& _v2fPosition, Vector2f& _v2fTarget, Vector2f& _v2fVelocity, const float _fMaxVelocity, const float fMaxForce, const float _fMass = 1.0f)
	{
		sf::Vector2f v2fDesiredVelocity = Normalise(_v2fTarget - _v2fPosition) * _fMaxVelocity;
		sf::Vector2f v2fSteeringForce = v2fDesiredVelocity - _v2fVelocity;
		v2fSteeringForce = Truncate(v2fSteeringForce, fMaxForce);
		
		_v2fVelocity += (v2fSteeringForce / _fMass) * fDeltatime;
		_v2fVelocity = Truncate(_v2fVelocity, _fMaxVelocity);
	}

	Vector2f GetWanderTargetPosition(Vector2f& _v2fPosition, const float _fWanderDistance, const float _fWanderRadius, Vector2f& _v2fVelocity, const float _fMaxVelocity, const float fMaxForce, const float _fMass = 1.0f)
	{
		float fWanderAngle = (rand() % 360) * (3.141592653589793238463f / 180.0f);
		Vector2f v2fTarget(cosf(fWanderAngle), sinf(fWanderAngle));
		v2fTarget *= _fWanderRadius;
		v2fTarget += _v2fPosition + (Normalise(_v2fVelocity) * _fWanderDistance);

		return v2fTarget;
	}
}