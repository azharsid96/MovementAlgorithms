#include "DynamicSeek.h"

DynamicSeek::DynamicSeek(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude)
{
	this->character = character;
	this->target = target;
	this->maxAccelerationMagnitude = maxAccelerationMagnitude;
}

_dynamicOutput DynamicSeek::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable

	// Acceleration update
	output.linear = target->position - character->position;

	output.linear.normalize();
	output.linear *= maxAccelerationMagnitude;

	// Angular accel. update
	output.angular = 0.0f;

	return output;
}
