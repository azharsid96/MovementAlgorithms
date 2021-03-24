#include "DynamicWander.h"

DynamicWander::DynamicWander(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude, float wanderRadius, float closeRadius)
{
	this->character = character;
	// this will be manipulated internally
	rigidbody internalTarget = { ofVec2f::zero(), 0.0f, ofVec2f::zero(), 0.0f };
	this->target = target;
	//this->target = target;
	this->maxAccelerationMagnitude = maxAccelerationMagnitude;
	this->wanderRadius = wanderRadius;
	this->closeRadius = closeRadius;

	this->dynamicSeek = new DynamicSeek(character, target, maxAccelerationMagnitude);
}

_dynamicOutput DynamicWander::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable

	// Check if boid is close to the target. If close, then find a new target
	if ((character->position - target->position).length() <= closeRadius) {
		target->position = ofVec2f(ofRandom(0, ofGetWindowWidth()), ofRandom(0, ofGetWindowHeight()));
	}

	// Find a random target within the wander radius around the boid
	while ((character->position - target->position).length() > wanderRadius) {
		target->position = ofVec2f(ofRandom(0, ofGetWindowWidth()), ofRandom(0, ofGetWindowHeight()));
	}

	output.linear = dynamicSeek->getDynamicSteering().linear;

	output.angular = 0.0f;

	return output;
}
