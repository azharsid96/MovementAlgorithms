#pragma once
#include <stdio.h>

#include "types.h"
#include "DynamicBehavior.h"

class DynamicSeek : public DynamicBehavior {

public:
	rigidbody * character;
	rigidbody * target;
	float maxAccelerationMagnitude;

	DynamicSeek(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude);

	_dynamicOutput getDynamicSteering();
};