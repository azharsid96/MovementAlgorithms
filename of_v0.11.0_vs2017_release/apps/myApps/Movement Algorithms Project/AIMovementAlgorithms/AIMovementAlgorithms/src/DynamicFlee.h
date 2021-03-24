#pragma once
#include <stdio.h>

#include "types.h"
#include "DynamicBehavior.h"

class DynamicFlee : public DynamicBehavior {

public:
	rigidbody * character;
	rigidbody * target;
	float maxAccelerationMagnitude;

	DynamicFlee(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude);

	_dynamicOutput getDynamicSteering();
};