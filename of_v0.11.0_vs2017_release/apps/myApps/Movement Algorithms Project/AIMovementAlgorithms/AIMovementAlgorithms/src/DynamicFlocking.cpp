#include "DynamicFlocking.h"

// position 
ofVec2f getFlocksCenterOfMass(vector<Boid*> *flockBoids, Boid* leaderBoid) {

	float xPosTotal = 0;
	float yPosTotal = 0;
	float massTotal = 0;

	for (vector<Boid*>::iterator it = begin(*flockBoids); it != end(*flockBoids); ++it)
	{
		Boid * boid = *it;

		xPosTotal += boid->mass * boid->getPosition().x;
		yPosTotal += boid->mass * boid->getPosition().y;
		massTotal += boid->mass;
	}

	massTotal += leaderBoid->mass;
	xPosTotal += leaderBoid->mass * leaderBoid->getPosition().x;
	yPosTotal += leaderBoid->mass * leaderBoid->getPosition().y;

	float xAvgPos = xPosTotal / massTotal;
	float yAvgPos = yPosTotal / massTotal;

	return ofVec2f(xAvgPos, yAvgPos);
}

ofVec2f getFlocksAvgVelocity(vector<Boid*> *flockBoids) {

	ofVec2f velocityTotal = ofVec2f::zero();
	/*float yPosTotal = 0;
	float massTotal = 0;*/

	for (vector<Boid*>::iterator it = begin(*flockBoids); it != end(*flockBoids); ++it)
	{
		Boid * boid = *it;

		velocityTotal += boid->getRigidbody()->velocity;
	}

	return velocityTotal / (*flockBoids).size();
}

DynamicFlocking::DynamicFlocking(vector<Boid*> *flockingBoids, Boid * leaderBoid, float slowRadius, float targetRadius, float timeToDesiredVelocity,
								float repulsionForceCoefficient, float personalSpaceRadius, float slowAngle, float targetAngle, float timeToDesiredRotation)
{
	this->flockingBoids = flockingBoids;
	this->leaderBoid = leaderBoid;
	this->leaderBoid->mass = 100.0f;
	this->slowRadius = slowRadius;
	this->targetRadius = targetRadius;
	this->timeToDesiredVelocity = timeToDesiredVelocity;
	this->repulsionForceCoefficient = repulsionForceCoefficient;
	this->personalSpaceRadius = personalSpaceRadius;
	this->slowAngle = slowAngle;
	this->targetAngle = targetAngle;
	this->timeToDesiredRotation = timeToDesiredRotation;
	

	for (vector<Boid*>::iterator it = begin(*flockingBoids); it != end(*flockingBoids); ++it)
	{
		Boid * boid = *it;
		

		// Add boids to separate from for each boid
		for (vector<Boid*>::iterator itr = begin(*flockingBoids); itr != end(*flockingBoids); ++itr)
		{
			Boid * otherBoid = *itr;
			if (boid != otherBoid) {
				boid->separateFromTheseBoids.push_back(otherBoid->getRigidbody());
			}
		}
	}
}

void DynamicFlocking::UpdateFlockingBehaviors()
{
	dynamicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable

	for (vector<Boid*>::iterator it = begin(*flockingBoids); it != end(*flockingBoids); ++it)
	{
		Boid * boid = *it;
		//boid->setDynamicInput(dynamicBlendedBehavior->getDynamicSteering());

		DynamicSeparation dynamicSeparation = DynamicSeparation(boid->getRigidbody(), &boid->separateFromTheseBoids, boid->maxAccelerationMagnitude, 
			repulsionForceCoefficient, personalSpaceRadius);


		rigidbody targetRigidbody;

		targetRigidbody.position = getFlocksCenterOfMass(flockingBoids, leaderBoid);

		DynamicArrive dynamicArrive = DynamicArrive(boid->getRigidbody(), &targetRigidbody, boid->maxAccelerationMagnitude, boid->maxSpeed,
			slowRadius, targetRadius, timeToDesiredVelocity);

		targetRigidbody.velocity = getFlocksAvgVelocity(flockingBoids);

		DynamicVelocityMatch dynamicVelocityMatch = DynamicVelocityMatch(boid->getRigidbody(), &targetRigidbody, boid->maxAccelerationMagnitude, boid->maxSpeed, timeToDesiredVelocity);


		DynamicLookWhereYouAreGoing dynamicLookWhereYouAreGoing = DynamicLookWhereYouAreGoing(boid->getRigidbody(), boid->maxAngularAccelerationMagnitude, boid->maxAngularSpeed, slowAngle, targetAngle,
			timeToDesiredRotation);

		DynamicBlendedBehavior dynamicBlendedBehavior = DynamicBlendedBehavior(boid->maxAccelerationMagnitude, boid->maxAngularAccelerationMagnitude);

		dynamicBlendedBehavior.addWeightedDynamicBehavior(&dynamicSeparation, 1.0f);
		dynamicBlendedBehavior.addWeightedDynamicBehavior(&dynamicArrive, 0.6f);
		dynamicBlendedBehavior.addWeightedDynamicBehavior(&dynamicVelocityMatch, 0.4f);
		dynamicBlendedBehavior.addWeightedDynamicBehavior(&dynamicLookWhereYouAreGoing, 1.0f);

		boid->setDynamicInput(dynamicBlendedBehavior.getDynamicSteering());

	}
}


