#pragma once
#include <stdio.h>

#include "types.h"
#include "DynamicFlee.h"
#include "DynamicBehavior.h"

class DynamicEvade : public DynamicBehavior {

	DynamicFlee * dynamicFlee = NULL;

public:
	rigidbody * character;
	rigidbody * target;
	float maxAccelerationMagnitude;
	float repulsionForceCoefficient;
	float personalSpaceRadius;

	DynamicEvade(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude, float repulsionForceCoefficient, float personalSpaceRadius);

	_dynamicOutput getDynamicSteering();
};