#pragma once
#include <stdio.h>

#include "types.h"
#include "DynamicBehavior.h"

class DynamicVelocityMatch : public DynamicBehavior {

public:
	rigidbody * character;
	rigidbody * target;
	float maxAccelerationMagnitude;
	float maxSpeed;
	float timeToDesiredVelocity;	// time for lerp to look consistent

	DynamicVelocityMatch(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude, float maxSpeed, float timeToDesiredVelocity);

	_dynamicOutput getDynamicSteering();
};