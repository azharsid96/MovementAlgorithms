#pragma once
#include <stdio.h>

#include "types.h"
#include "DynamicSeek.h"
#include "DynamicBehavior.h"

class DynamicWander : public DynamicBehavior {

	DynamicSeek * dynamicSeek = NULL;

public:

	rigidbody * character;
	rigidbody * target;
	float maxAccelerationMagnitude;
	float wanderRadius;	// radius around the boid to find random point within
	float closeRadius;	// radius around the wander point within which to find a new random point

	DynamicWander(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude, float wanderRadius, float closeRadius);

	_dynamicOutput getDynamicSteering();
};
