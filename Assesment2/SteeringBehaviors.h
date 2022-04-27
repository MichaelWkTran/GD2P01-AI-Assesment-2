#pragma once
#include "SFML/System/Vector2.hpp"
#include "Vector2Methods.h"
#include "ExternalVariables.h"
#include <stdlib.h>
#include <time.h>

using namespace sf;

namespace SteeringBehaviours
{
	void AddForce(Vector2f _v2fForce, Vector2f& _v2fVelocity, const float _fMaxVelocity, const float _fMaxForce, const float _fMass = 1.0f)
	{
		_v2fVelocity += (Truncate(_v2fForce, _fMaxForce) / _fMass) * fDeltatime;
		_v2fVelocity = Truncate(_v2fVelocity, _fMaxVelocity);
	}

	Vector2f Seek
	(
		const Vector2f& _v2fPosition, 
		const Vector2f& _v2fTarget, 
		Vector2f& _v2fVelocity, 
		const float _fMaxVelocity
	)
	{
		Vector2f v2fDesiredVelocity = Normalise(_v2fTarget - _v2fPosition) * _fMaxVelocity;
		return v2fDesiredVelocity - _v2fVelocity;
	}

	Vector2f Flee
	(
		const Vector2f& _v2fPosition,
		const Vector2f& _v2fTarget,
		Vector2f& _v2fVelocity,
		const float _fMaxVelocity
	)
	{
		return Seek(_v2fTarget, _v2fPosition, _v2fVelocity, _fMaxVelocity);
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

	Vector2f Arrive
	(
		const float _fSlowingRadius,
		Vector2f& _v2fPosition, 
		Vector2f& _v2fTarget, 
		Vector2f& _v2fVelocity, 
		const float _fMaxVelocity
	)
	{
		Vector2f v2fTargetOffset = _v2fTarget - _v2fPosition;
		float fDistance = Magnitude(v2fTargetOffset);
		
		if (fDistance < _fSlowingRadius)
		{
			Vector2f v2fDesiredVelocity = Normalise(v2fTargetOffset) * _fMaxVelocity * (fDistance / _fSlowingRadius);
			return v2fDesiredVelocity - _v2fVelocity;
		}

		return Seek(_v2fPosition, _v2fTarget, _v2fVelocity, _fMaxVelocity);
	}

	Vector2f GetWanderTargetPosition
	(
		const float _fWanderDistance, 
		const float _fWanderRadius, 
		Vector2f& _v2fPosition, 
		Vector2f& _v2fVelocity
	)
	{
		float fWanderAngle = (rand() % 360) * (3.141592653589793238463f / 180.0f);
		Vector2f v2fTarget(cosf(fWanderAngle), sinf(fWanderAngle));
		v2fTarget *= _fWanderRadius;
		v2fTarget += _v2fPosition + (Normalise(_v2fVelocity) * _fWanderDistance);

		return v2fTarget;
	}

	Vector2f Separation
	(
		float fSeparationRadius,
		std::vector<Vector2f> _vNeighbours,
		Vector2f& _v2fPosition,
		Vector2f& _v2fVelocity,
		const float _fMaxVelocity
	)
	{
		if (_vNeighbours.size() == 0) return Vector2f();

		//Vector2f v2fCenterOfMass = _v2fPosition;
		//for (int i = 0; i < (int)_vNeighbours.size(); i++) v2fCenterOfMass += _vNeighbours[i];
		//v2fCenterOfMass /= (float)_vNeighbours.size();
		//
		//return Flee(_v2fPosition, v2fCenterOfMass, _v2fVelocity, _fMaxVelocity);
		//Vector2f v2fDifference = _v2fPosition - v2fCenterOfMass;
		//Vector2f v2fDesiredVelocity = Normalise(v2fDifference) * _fMaxVelocity * ((Magnitude(v2fDifference) - fSeparationRadius) / (-fSeparationRadius));



		Vector2f v2fDesiredVelocity;
		for (int i = 0; i < (int)_vNeighbours.size(); i++)
		{
			Vector2f v2fDifference = _v2fPosition - _vNeighbours[i];
			//if (v2fDifference == Vector2f())
			//{
			//	float fVectorAngle = (rand() % 360) * (3.141592653589793238463f / 180.0f);
			//	v2fDifference = Vector2f(cosf(fVectorAngle), sinf(fVectorAngle));
			//}
			
			v2fDesiredVelocity += Normalise(v2fDifference) * _fMaxVelocity * ((Magnitude(v2fDifference) - fSeparationRadius)/(-fSeparationRadius));
		}	
		v2fDesiredVelocity /= (float)_vNeighbours.size();

		return v2fDesiredVelocity - _v2fVelocity;
	}

	Vector2f GetCohesionCentreOfMass
	(
		std::vector<Vector2f> _vNeighbours,
		Vector2f& _v2fPosition
	)
	{
		if (_vNeighbours.size() == 0) return Vector2f();

		Vector2f v2fCenterOfMass = _v2fPosition;
		for (int i = 0; i < (int)_vNeighbours.size(); i++) v2fCenterOfMass += _vNeighbours[i];
		return v2fCenterOfMass / (float)_vNeighbours.size();
	}

	Vector2f Alignment
	(
		std::vector<Vector2f> _vNeighbourPositions,
		std::vector<Vector2f> _vNeighbourVelocities,
		Vector2f& _v2fVelocity
	)
	{
		if (_vNeighbourPositions.size() == 0 && _vNeighbourPositions.size() == _vNeighbourVelocities.size()) return Vector2f();

		//Calculate Average Velocity
		Vector2f v2fAverageVelocity;
		unsigned int uMovingAgentCount = 0;
		for (int i = 0; i < (int)_vNeighbourPositions.size(); i++)
		{
			if (_vNeighbourPositions[i] == Vector2f()) continue;
			
			v2fAverageVelocity += _vNeighbourPositions[i];
			uMovingAgentCount++;
		}
		v2fAverageVelocity /= (float)uMovingAgentCount;

		return v2fAverageVelocity - _v2fVelocity;
	}
}