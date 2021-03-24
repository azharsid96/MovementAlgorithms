#include "DynamicPursue.h"

DynamicPursue::DynamicPursue(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude, float maxPredictionTime)
{
	this->character = character;
	this->target = target;
	this->maxAccelerationMagnitude = maxAccelerationMagnitude;
	this->maxPredictionTime = maxPredictionTime;
	this->dynamicSeek = new DynamicSeek(character, target, maxAccelerationMagnitude);
}

_dynamicOutput DynamicPursue::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable

	// 1. Calculate intermediate target (new position)

	// we need: scale the time window we use
	float actualPredictionTime = 0.0f;

	// calculate distance to target
	ofVec2f direction = target->position - character->position;
	float distance = direction.length();
	float characterSpeed = character->velocity.length();

	// calculate speed needed to catch our target
	float speedNeededToCatchTarget = distance / maxPredictionTime;

	// if speed needed > current speed, use max prediction time
	if (speedNeededToCatchTarget > characterSpeed)
		actualPredictionTime = maxPredictionTime;

	// else, scale prediction time
	else
		actualPredictionTime = distance / characterSpeed;

	// target position = target current position + (target's velocity * acutal prediction time)
	ofVec2f offset = target->velocity * actualPredictionTime;
	ofVec2f pursueTarget(target->position);
	pursueTarget += offset;

	// 2. Delegate
	rigidbody rigidbodyTarget = { pursueTarget, target->orientation,
	target->velocity, target->rotation };

	this->dynamicSeek->target = &rigidbodyTarget;	// we want to be pursuing this fake target that's going to help us catch up to our real target

	output.linear = dynamicSeek->getDynamicSteering().linear;

	// Angular accel. update
	output.angular = 0.0f;

	return output;
}
