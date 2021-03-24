#include "DynamicSeparation.h"

DynamicSeparation::DynamicSeparation(rigidbody * character, vector<rigidbody*> *targets, float maxAccelerationMagnitude, float repulsionForceCoefficient, float personalSpaceRadius)
{
	this->character = character;
	this->targets = targets;
	this->maxAccelerationMagnitude = maxAccelerationMagnitude;
	this->repulsionForceCoefficient = repulsionForceCoefficient;
	this->personalSpaceRadius = personalSpaceRadius;

	rigidbody * firstTargetRigidbody = (*targets)[0];

	this->dynamicEvade = new DynamicEvade(character, firstTargetRigidbody, maxAccelerationMagnitude, repulsionForceCoefficient, personalSpaceRadius);
}

_dynamicOutput DynamicSeparation::getDynamicSteering()
{
	dynamicOutput steeringAccumulator = { ofVec2f::zero(), 0.0f };
	dynamicOutput steering = { ofVec2f::zero(), 0.0f };		// define the return variable

	// Go through all targets to evade
	for (vector<rigidbody*>::iterator it = begin(*targets); it != end(*targets); it++)
	{
		// 1. Calculate intermediate target (new position)
		rigidbody * target = *it;
		this->dynamicEvade->target = target;

		// 2. Delegate
		steering.linear = this->dynamicEvade->getDynamicSteering().linear;

		// Accumulate
		steeringAccumulator.linear += steering.linear;
	}

	// Angular accel. update
	steeringAccumulator.angular = 0.0f;

	// 3. Return accumulation of accelerations
	return steeringAccumulator;
}
