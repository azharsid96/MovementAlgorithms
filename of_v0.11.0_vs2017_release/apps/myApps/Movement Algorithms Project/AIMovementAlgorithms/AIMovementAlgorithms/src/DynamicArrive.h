#pragma once
#include <stdio.h>

#include "types.h"
#include "DynamicBehavior.h"

class DynamicArrive : public DynamicBehavior {

public:
	rigidbody * character;
	rigidbody * target;
	float maxAccelerationMagnitude;
	float maxSpeed;
	float slowRadius;				// radius around target, begin to slow down
	float targetRadius;				// radius to stop moving
	float timeToDesiredVelocity;	// time for lerp to look consistent

	DynamicArrive(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude, float maxSpeed, float slowRadius, float targetRadius, float timeToDesiredVelocity);

	_dynamicOutput getDynamicSteering();
};