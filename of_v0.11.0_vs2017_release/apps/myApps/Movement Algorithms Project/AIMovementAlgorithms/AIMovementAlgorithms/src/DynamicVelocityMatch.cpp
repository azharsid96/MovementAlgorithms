#include "DynamicVelocityMatch.h"

DynamicVelocityMatch::DynamicVelocityMatch(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude, float maxSpeed, float timeToDesiredVelocity)
{
	this->character = character;
	this->target = target;
	this->maxAccelerationMagnitude = maxAccelerationMagnitude;
	this->maxSpeed = maxSpeed;
	this->timeToDesiredVelocity = timeToDesiredVelocity;
}

_dynamicOutput DynamicVelocityMatch::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable

	// accelerate to that difference between boid's current and target's current velocity
	output.linear = (target->velocity - character->velocity) / timeToDesiredVelocity;

	// clamp to max acceleration
	if (output.linear.length() > maxAccelerationMagnitude) {
		output.linear.normalize();
		output.linear *= maxAccelerationMagnitude;
	}

	// Angular accel. update
	output.angular = 0.0f;

	return output;
}
