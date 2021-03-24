#pragma once
#include <stdio.h>
#include <vector>

#include "types.h"
#include "Boid.h"
#include "DynamicArrive.h"
#include "DynamicVelocityMatch.h"
#include "DynamicSeparation.h"
#include "DynamicLookWhereYouAreGoing.h"
#include "DynamicBlendedBehavior.h"

class DynamicFlocking {

	/*DynamicArrive * dynamicArrive = NULL;
	DynamicVelocityMatch * dynamicVelocityMatch = NULL;
	DynamicSeparation *dynamicSeparation = NULL;
	DynamicLookWhereYouAreGoing * dynamicLookWhereYouAreGoing = NULL;
	DynamicBlendedBehavior * dynamicBlendedBehavior = NULL;
	//vector<rigidbody*> separateFromTheseBoids;*/

public:
	rigidbody * character;
	rigidbody * target;
	float maxAccelerationMagnitude;
	float repulsionForceCoefficient;
	float personalSpaceRadius;
	float slowRadius;				// radius around target, begin to slow down
	float targetRadius;				// radius to stop moving
	float timeToDesiredVelocity;	// time for lerp to look consistent
	float slowAngle;
	float targetAngle;
	float timeToDesiredRotation;
	vector<Boid*> *flockingBoids;
	Boid * leaderBoid;


	DynamicFlocking(vector<Boid*> *flockingBoids, Boid * leaderBoid, float slowRadius, float targetRadius, float timeToDesiredVelocity,
					float repulsionForceCoefficient, float personalSpaceRadius, float slowAngle, float targetAngle, float timeToDesiredRotation);

	void UpdateFlockingBehaviors();
};