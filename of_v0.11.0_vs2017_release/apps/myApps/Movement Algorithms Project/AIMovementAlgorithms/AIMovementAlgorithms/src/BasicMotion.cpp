#include "BasicMotion.h"

BasicMotion::BasicMotion(rigidbody * character, rigidbody * target, float maxSpeed, ofVec2f characterStartCooridnate,
	float offsetScreenWidth, float offsetScreenHeight, float offset)
{
	this->character = character;
	this->target = target;
	this->maxSpeed = maxSpeed;
	this->characterStartCoordinate = characterStartCooridnate;
	this->offsetScreenWidth = offsetScreenWidth;
	this->offsetScreenHeight = offsetScreenHeight;
	this->offset = offset;
}

_kinematicOutput BasicMotion::getKinematicSteering()
{
	kinematicOutput output = { ofVec2f::zero(), 0.0f };		// define the return variable

	// Velocity update
	output.velocity = target->position - character->position;
	output.velocity.normalize();
	output.velocity *= maxSpeed;
	
	// make the character boid chase the target around the screen
	if (character->position.distance(ofVec2f(offset, offset)) < 2.0f) {
		target->position = (ofVec2f(offsetScreenWidth, offset));
		character->orientation = 0.0f;
	}
	else if (character->position.distance(ofVec2f(offsetScreenWidth, offset)) < 2.0f) {
		target->position = (ofVec2f(offsetScreenWidth, offsetScreenHeight));
		character->orientation = 1.57f;
	}
	else if (character->position.distance(ofVec2f(offsetScreenWidth, offsetScreenHeight)) < 2.0f) {
		target->position = (ofVec2f(offset, offsetScreenHeight));
		character->orientation = 3.14f;		// looks left
	}

	return output;
}
