#include "DynamicFlee.h"

DynamicFlee::DynamicFlee(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude)
{
	this->character = character;
	this->target = target;
	this->maxAccelerationMagnitude = maxAccelerationMagnitude;
}

_dynamicOutput DynamicFlee::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable

	// Acceleration update
	output.linear = character->position - target->position;

	output.linear.normalize();
	output.linear *= maxAccelerationMagnitude;

	// Angular accel. update
	output.angular = 0.0f;

	return output;
}
