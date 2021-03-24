#pragma once
#include <stdio.h>

#include "types.h"
#include "DynamicSeek.h"
#include "DynamicBehavior.h"

class DynamicPursue : public DynamicBehavior {

	DynamicSeek * dynamicSeek = NULL;

public:
	rigidbody * character;
	rigidbody * target;
	float maxAccelerationMagnitude;
	float maxPredictionTime;	// how far into the future do we predict

	DynamicPursue(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude, float maxPredictionTime);

	_dynamicOutput getDynamicSteering();
};
