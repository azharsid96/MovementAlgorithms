#pragma once
#include <stdio.h>

#include "types.h"
#include "DynamicAlign.h"
#include "DynamicBehavior.h"

class DynamicLookWhereYouAreGoing : public DynamicBehavior {

	DynamicAlign * dynamicAlign = NULL;
	rigidbody * target;

public:
	rigidbody * character;

	DynamicLookWhereYouAreGoing(rigidbody * character, float maxAngularAccelerationMagnitude, float maxAngularSpeed, float slowAngle,
		float targetAngle, float timeToDesiredRotation);

	_dynamicOutput getDynamicSteering();
};