#pragma once
#include <stdio.h>

#include "types.h"
#include "DynamicAlign.h"
#include "DynamicBehavior.h"

class DynamicFace : public DynamicBehavior {

	DynamicAlign * dynamicAlign = NULL;
	rigidbody * cloneTarget;

public:
	rigidbody * character;
	rigidbody * target;

	DynamicFace(rigidbody * character, rigidbody * target, float maxAngularAccelerationMagnitude, float maxAngularSpeed, float slowAngle,
		float targetAngle, float timeToDesiredRotation);

	_dynamicOutput getDynamicSteering();
};