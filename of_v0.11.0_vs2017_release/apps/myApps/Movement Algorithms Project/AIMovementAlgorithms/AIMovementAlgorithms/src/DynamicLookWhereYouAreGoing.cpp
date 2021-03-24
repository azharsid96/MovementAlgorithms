#include "DynamicLookWhereYouAreGoing.h"

DynamicLookWhereYouAreGoing::DynamicLookWhereYouAreGoing(rigidbody * character, float maxAngularAccelerationMagnitude, float maxAngularSpeed, float slowAngle, float targetAngle, float timeToDesiredRotation)
{
	this->character = character;
	// this will be manipulated internally
	rigidbody internalTarget = { ofVec2f::zero(), 0.0f, ofVec2f::zero(), 0.0f };
	this->target = &internalTarget;

	this->dynamicAlign = new DynamicAlign(character, &internalTarget, maxAngularAccelerationMagnitude, maxAngularSpeed, slowAngle, targetAngle, timeToDesiredRotation);
}

_dynamicOutput DynamicLookWhereYouAreGoing::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable

	// 1. Calculate intermediate target (new position)
	float characterVelocityAngle = atan2(this->character->velocity.y, this->character->velocity.x);
	this->target->orientation = characterVelocityAngle;


	// 2. Delegate
	output.angular = dynamicAlign->getDynamicSteering().angular;

	output.linear = ofVec2f::zero();

	// return dynamicAlign->getDynamicSteering();
	return output;
}
