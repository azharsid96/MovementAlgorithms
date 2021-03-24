#include "DynamicArrive.h"

DynamicArrive::DynamicArrive(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude, float maxSpeed, float slowRadius, float targetRadius, float timeToDesiredVelocity)
{
	this->character = character;
	this->target = target;
	this->maxAccelerationMagnitude = maxAccelerationMagnitude;
	this->maxSpeed = maxSpeed;
	this->slowRadius = slowRadius;
	this->targetRadius = targetRadius;
	this->timeToDesiredVelocity = timeToDesiredVelocity;
}

_dynamicOutput DynamicArrive::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable
	//dynamicOutput output = currentDynamicInput;

	ofVec2f direction = target->position - character->position;
	float distanceToTarget = direction.length();

	// caclulate the magnitude of your velocity to match 
	float desiredSpeed = 0.0f;

	// if we're there, stop moving
	if (distanceToTarget < targetRadius) {

		//return { character->velocity * -0.4f, 0.0f };
		return { ofVec2f::zero(), 0.0f };
	}

	// if we're outside the slow radius, move at max speed
	if (distanceToTarget > slowRadius) {
		desiredSpeed = maxSpeed;
	}

	// else, move at lerp'd speed
	else {
		desiredSpeed = maxSpeed * (distanceToTarget / slowRadius);
	}

	// caclulate the direction, combine with velocity
	direction.normalize();
	ofVec2f desiredVelocity = (direction) * desiredSpeed;

	// accelerate to that difference between current and desired velocity
	output.linear = (desiredVelocity - character->velocity) / timeToDesiredVelocity;

	// clamp to max acceleration
	if (output.linear.length() > maxAccelerationMagnitude) {
		output.linear.normalize();
		output.linear *= maxAccelerationMagnitude;
	}

	// Angular accel. update
	output.angular = 0;

	return output;
}
