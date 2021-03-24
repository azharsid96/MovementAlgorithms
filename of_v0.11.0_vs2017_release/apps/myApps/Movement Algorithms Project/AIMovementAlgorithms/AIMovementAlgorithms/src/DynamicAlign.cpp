#include "DynamicAlign.h"

float mapToPiRange(float angleInRadians) {
	float mappedValue = angleInRadians;

	while (mappedValue > glm::pi<float>()) {
		mappedValue -= glm::two_pi<float>();
	}

	while (mappedValue < -glm::pi<float>()) {
		mappedValue += glm::two_pi<float>();
	}

	return mappedValue;

}

DynamicAlign::DynamicAlign(rigidbody * character, rigidbody * target, float maxAngularAccelerationMagnitude, float maxAngularSpeed, float slowAngle,
	float targetAngle, float timeToDesiredRotation)
{
	this->character = character;
	this->target = target;
	this->maxAngularAccelerationMagnitude = maxAngularAccelerationMagnitude;
	this->maxAngularSpeed = maxAngularSpeed;
	this->slowAngle = slowAngle;
	this->targetAngle = targetAngle;
	this->timeToDesiredRotation = timeToDesiredRotation;
}

_dynamicOutput DynamicAlign::getDynamicSteering()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable
	//dynamicOutput output = { character->dynamicLinear, 0.0f };

	// calculate the angular speed to match
	float orientationChange = target->orientation - character->orientation;
	float smallestChange = mapToPiRange(orientationChange);

	float angularDistance = fabs(smallestChange);		// orientation distance to target
	float targetRotation = 0.0f;	// angular velocity to match

	// if we're there, stop moving
	if (angularDistance < targetAngle)
		//return { ofVec2f::zero(), character->rotation * -0.4f };
		return { ofVec2f::zero(), 0.0f };
		//return output;

	// if we're outside the slow angle, rotate at max angular speed
	else if (angularDistance > slowAngle) {
		targetRotation = maxAngularSpeed;
	}

	// else, move at lerp'd speed (between slow and target angles)
	else {
		targetRotation = maxAngularSpeed * (angularDistance / slowAngle);
	}

	// caclulate the direction of rotation, combine with velocity
	float accelerationSign = (smallestChange / angularDistance);	// will be +/- depending on smallestChange

	targetRotation *= accelerationSign;	

	// accelerate to the difference between current rotation and desired rotation
	output.angular = (targetRotation - character->rotation) / timeToDesiredRotation;

	// clamp to max angular acceleration
	if (fabs(output.angular) > maxAngularAccelerationMagnitude) {
		output.angular = maxAngularAccelerationMagnitude * accelerationSign;
	}

	output.linear = ofVec2f::zero();

	return output;
}
