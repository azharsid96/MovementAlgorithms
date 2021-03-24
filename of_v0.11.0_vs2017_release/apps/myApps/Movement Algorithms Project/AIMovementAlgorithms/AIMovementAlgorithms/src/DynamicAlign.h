#pragma once
#include <stdio.h>

#include "types.h"
#include "DynamicBehavior.h"

class DynamicAlign : public DynamicBehavior {

public:
	rigidbody * character;
	rigidbody * target;
	float maxAngularAccelerationMagnitude;
	float maxAngularSpeed;
	float slowAngle;				// orientation at which to begin slowing angular acceleration
	float targetAngle;				// orientation at which to stop accelerating
	float timeToDesiredRotation;	// time for lerp to look consistent

	DynamicAlign(rigidbody * character, rigidbody * target, float maxAngularAccelerationMagnitude, float maxAngularSpeed, float slowAngle,
				float targetAngle, float timeToDesiredRotation);

	_dynamicOutput getDynamicSteering();
};