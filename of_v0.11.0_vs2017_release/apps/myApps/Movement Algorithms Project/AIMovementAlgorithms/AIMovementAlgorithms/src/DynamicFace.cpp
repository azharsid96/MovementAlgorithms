#include "DynamicFace.h"

DynamicFace::DynamicFace(rigidbody * character, rigidbody * target, float maxAngularAccelerationMagnitude, float maxAngularSpeed, float slowAngle, float targetAngle, float timeToDesiredRotation)
{
	this->character = character;
	// this will be manipulated internally
	this->cloneTarget = target;
	this->target = target;

	this->dynamicAlign = new DynamicAlign(character, cloneTarget, maxAngularAccelerationMagnitude, maxAngularSpeed, slowAngle, targetAngle, timeToDesiredRotation);
}

_dynamicOutput DynamicFace::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable

	// 1. Calculate intermediate target (new position)
	ofVec2f direction = target->position - character->position;
	float characterVelocityAngle = atan2(direction.y, direction.x);

	cloneTarget->orientation = characterVelocityAngle;


	// 2. Delegate
	output.angular = dynamicAlign->getDynamicSteering().angular;

	output.linear = ofVec2f::zero();

	// return dynamicAlign->getDynamicSteering();
	return output;
}
