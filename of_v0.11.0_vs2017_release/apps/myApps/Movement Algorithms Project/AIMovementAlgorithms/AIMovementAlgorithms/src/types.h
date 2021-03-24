#pragma once

#include "ofMain.h"

typedef struct _rigidbody {
	ofVec2f position = ofVec2f::zero();									// x,z components
	float orientation = 0.0f;									// angle in radians (+/- direction)
	ofVec2f velocity = ofVec2f::zero();									// x,z components of velocity
	float rotation = 0.0f;										// angular velocity in radians
} rigidbody, *pRigidbody;

typedef struct _kinematicOutput {
	ofVec2f velocity = ofVec2f::zero();		// x,z components
	float rotation = 0;			// angle in radians (+/- direction)
} kinematicOutput;

typedef struct _dynamicOutput {
	ofVec2f linear = ofVec2f::zero();			// x,z components of acceleration
	float angular = 0;			// angle in radians/time/time (+/- direction)
} dynamicOutput;
