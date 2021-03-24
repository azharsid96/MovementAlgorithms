#include "DynamicBlendedBehavior.h"

DynamicBlendedBehavior::DynamicBlendedBehavior(float maxAccelerationMagnitude, float maxAngularAccelerationMagnitude)
{
	this->maxAccelerationMagnitude = maxAccelerationMagnitude;
	this->maxAngularAccelerationMagnitude = maxAngularAccelerationMagnitude;
}

DynamicBlendedBehavior::~DynamicBlendedBehavior()
{
	// need to destruct the weighted behaviors that are allocated 
	for (auto it = begin(behaviors); it != end(behaviors); ++it)
	{
		weightedDynamicBehavior * weightedDynamicBehaviorPtr = *it; 
		delete weightedDynamicBehaviorPtr;
	}

	behaviors.clear();	// clear the behaviors out
}

dynamicOutput DynamicBlendedBehavior::getDynamicSteering()
{
	dynamicOutput blendedOutput = { ofVec2f::zero(), 0.0f };		// define the return variable

	// for each behavior,
	for (int i = 0; i < behaviors.size(); i++)
	{
		weightedDynamicBehavior * weightedBehavior = behaviors[i];

		// get its output
		dynamicOutput weightedOutput = weightedBehavior->movementBehavior->getDynamicSteering();

		// multiply it against its weight
		weightedOutput.linear *= weightedBehavior->weight;
		weightedOutput.angular *= weightedBehavior->weight;

		// add outputs
		blendedOutput.linear += weightedOutput.linear;
		blendedOutput.angular += weightedOutput.angular;
	}
	
	// clamp to max acceleration
	if (blendedOutput.linear.length() > maxAccelerationMagnitude) {
		blendedOutput.linear.normalize();
		blendedOutput.linear *= maxAccelerationMagnitude;
	}

	// clamp to max angular acceleration
	if (fabs(blendedOutput.angular) > maxAngularAccelerationMagnitude) {
		int accelerationSign = blendedOutput.angular / abs(blendedOutput.angular);
		blendedOutput.angular = maxAngularAccelerationMagnitude * accelerationSign;
	}

	return blendedOutput;
}

void DynamicBlendedBehavior::addWeightedDynamicBehavior(DynamicBehavior * behavior, float behaviorWeight)
{
	weightedDynamicBehavior * newWeightedDynamicBehavior = new weightedDynamicBehavior();
	newWeightedDynamicBehavior->movementBehavior = behavior;
	newWeightedDynamicBehavior->weight = behaviorWeight;

	behaviors.push_back(newWeightedDynamicBehavior);
}
