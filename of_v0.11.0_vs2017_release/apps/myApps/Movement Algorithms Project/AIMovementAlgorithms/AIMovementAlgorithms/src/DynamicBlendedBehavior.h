#pragma once
#include <stdio.h>
#include <vector>

#include "types.h"
#include "DynamicBehavior.h"

typedef struct _weightedDynamicBehavior {
	DynamicBehavior * movementBehavior;
	float weight;
} weightedDynamicBehavior;

class DynamicBlendedBehavior : DynamicBehavior {

	vector<weightedDynamicBehavior*> behaviors;

public: 

	float maxAccelerationMagnitude;
	float maxAngularAccelerationMagnitude;

	// Constructs a blend of the single input movement
	DynamicBlendedBehavior(float maxAccelerationMagnitude, float maxAngularAccelerationMagnitude);

	dynamicOutput getDynamicSteering();

	// Adds a weighted dyanmic behavior to this blend
	void addWeightedDynamicBehavior(DynamicBehavior * behavior, float behaviorWeight);

	~DynamicBlendedBehavior();

};