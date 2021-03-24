#pragma once

#include <stdio.h>

#include "types.h"

class BasicMotion {

public:
	rigidbody * character;
	rigidbody * target;
	float maxSpeed;

	ofVec2f characterStartCoordinate;

	// Screen values
	float offsetScreenWidth;
	float offsetScreenHeight;
	float offset;

	BasicMotion(rigidbody * character, rigidbody * target, float maxSpeed, ofVec2f characterStartCooridnate,
		float offsetScreenWidth, float offsetScreenHeight, float offset);

	_kinematicOutput getKinematicSteering();

};
