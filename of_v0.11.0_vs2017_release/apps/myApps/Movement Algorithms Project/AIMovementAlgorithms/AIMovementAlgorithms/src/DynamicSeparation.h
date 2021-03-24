#pragma once
#include <stdio.h>
#include <vector>

#include "types.h"
#include "DynamicEvade.h"
#include "DynamicBehavior.h"

class DynamicSeparation : public DynamicBehavior {

	DynamicEvade * dynamicEvade = NULL;

public:
	rigidbody * character;
	vector<rigidbody*> *targets;		// rigidbodies to separate from
	float maxAccelerationMagnitude;
	float repulsionForceCoefficient;
	float personalSpaceRadius;

	DynamicSeparation(rigidbody * character, vector<rigidbody*> *targets, float maxAccelerationMagnitude, float repulsionForceCoefficient, float personalSpaceRadius);

	_dynamicOutput getDynamicSteering();
};