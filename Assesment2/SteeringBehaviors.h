#pragma once
#include "SFML/System/Vector2.hpp"
#include "Vector2Methods.h"
#include "ExternalVariables.h"
#include <stdlib.h>
#include <time.h>

using namespace sf;

namespace SteeringBehaviours
{
	void Seek
	(
		const Vector2f& _v2fPosition, 
		const Vector2f& _v2fTarget, 
		Vector2f& _v2fVelocity, 
		const float _fMaxVelocity, 
		const float fMaxForce, 
		const float _fMass = 1.0f
	)
	{
		Vector2f v2fDesiredVelocity = Normalise(_v2fTarget - _v2fPosition) * _fMaxVelocity;
		Vector2f v2fSteeringForce = v2fDesiredVelocity - _v2fVelocity;
		v2fSteeringForce = Truncate(v2fSteeringForce, fMaxForce);
		
		_v2fVelocity += (v2fSteeringForce / _fMass) * fDeltatime;
		_v2fVelocity = Truncate(_v2fVelocity, _fMaxVelocity);
	}

	void Flee
	(
		const Vector2f& _v2fPosition,
		const Vector2f& _v2fTarget,
		Vector2f& _v2fVelocity,
		const float _fMaxVelocity,
		const float fMaxForce,
		const float _fMass = 1.0f
	)
	{
		Seek(_v2fTarget, _v2fPosition, _v2fVelocity, _fMaxVelocity, fMaxForce, _fMass);
	}

	Vector2f GetPursueTargetPosition
	(
		const Vector2f& _v2fPosition,
		const Vector2f& _v2fTargetPosition,
		Vector2f& _v2fVelocity,
		const Vector2f& _v2fTargetVelocity,
		float fMaxPrediction
	)
	{
		float fSpeed = Magnitude(_v2fVelocity);
		float fDistance = Magnitude(_v2fTargetPosition - _v2fPosition);
		
		float fPrediction;
		if (fSpeed <= fDistance / fMaxPrediction) fPrediction = fMaxPrediction;
		else fPrediction = fDistance / fSpeed;

		return _v2fTargetPosition + (_v2fTargetVelocity * fPrediction);
	}

	void Arrive
	(
		const float _fSlowingRadius,
		Vector2f& _v2fPosition, 
		Vector2f& _v2fTarget, 
		Vector2f& _v2fVelocity, 
		const float _fMaxVelocity, 
		const float fMaxForce,
		const float _fMass = 1.0f
	)
	{
		Vector2f v2fTargetOffset = _v2fTarget - _v2fPosition;
		float fDistance = Magnitude(v2fTargetOffset);
		
		if (fDistance < _fSlowingRadius)
		{
			Vector2f v2fDesiredVelocity = Normalise(v2fTargetOffset) * _fMaxVelocity * (fDistance / _fSlowingRadius);
			Vector2f v2fSteeringForce = v2fDesiredVelocity - _v2fVelocity;
			v2fSteeringForce = Truncate(v2fSteeringForce, fMaxForce);

			_v2fVelocity += (v2fSteeringForce / _fMass) * fDeltatime;
			_v2fVelocity = Truncate(_v2fVelocity, _fMaxVelocity);
		}
		else
		{
			Seek(_v2fPosition, _v2fTarget, _v2fVelocity, _fMaxVelocity, fMaxForce, _fMass);
		}
	}

	Vector2f GetWanderTargetPosition
	(
		const float _fWanderDistance, 
		const float _fWanderRadius, 
		Vector2f& _v2fPosition, 
		Vector2f& _v2fVelocity, 
		const float _fMaxVelocity, 
		const float fMaxForce, 
		const float _fMass = 1.0f
	)
	{
		float fWanderAngle = (rand() % 360) * (3.141592653589793238463f / 180.0f);
		Vector2f v2fTarget(cosf(fWanderAngle), sinf(fWanderAngle));
		v2fTarget *= _fWanderRadius;
		v2fTarget += _v2fPosition + (Normalise(_v2fVelocity) * _fWanderDistance);

		return v2fTarget;
	}
}