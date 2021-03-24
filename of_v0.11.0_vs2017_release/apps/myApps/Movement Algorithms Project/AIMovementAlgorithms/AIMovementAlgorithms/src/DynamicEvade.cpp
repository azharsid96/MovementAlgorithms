#include "DynamicEvade.h"

DynamicEvade::DynamicEvade(rigidbody * character, rigidbody * target, float maxAccelerationMagnitude, float repulsionForceCoefficient, float personalSpaceRadius)
{
	this->character = character;
	this->target = target;
	this->maxAccelerationMagnitude = maxAccelerationMagnitude;
	this->repulsionForceCoefficient = repulsionForceCoefficient;
	this->personalSpaceRadius = personalSpaceRadius;

	this->dynamicFlee = new DynamicFlee(character, target, maxAccelerationMagnitude);
}

_dynamicOutput DynamicEvade::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable

	// 1. Calculate intermediate target (new position)

	// Calculate distance between character and target
	ofVec2f direction = target->position - character->position;
	float distance = direction.length();

	// If outside personal space, return nothing
	if (distance > personalSpaceRadius)
		return  { ofVec2f::zero(), 0.0f };

	// calculate repulsion force (we are guaranteed to be within personal space)
	float repulsion = repulsionForceCoefficient / (distance * distance);

	// take the minimum between repulsion and max acceleration
	float repulsionAcceleration = glm::min(repulsion, maxAccelerationMagnitude);

	// override dynamic flee's max acceleration
	dynamicFlee->maxAccelerationMagnitude = repulsionAcceleration;

	// 2. Delegate
	output.linear = dynamicFlee->getDynamicSteering().linear;

	// Angular accel. update
	output.angular = 0.0f;

	return output;
}
