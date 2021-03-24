#pragma once

#include <stdio.h>
#include <vector>

#include "types.h"
#include "ofMain.h"

class Boid
{
	float width = 32.0f;
	float radius = width / 2.0f;
	ofColor boidColor;
	rigidbody rigidbody;
	kinematicOutput kinematicInput;
	dynamicOutput dynamicInput;

public:
	float maxSpeed = 75.0f;
	float maxAccelerationMagnitude = 125.0f;
	float maxAngularSpeed = 2.5f;
	float maxAngularAccelerationMagnitude = maxAngularSpeed * 50.0f;
	float mass = 10.0f;

	vector<pRigidbody> separateFromTheseBoids;

	// Constructor
	Boid(ofVec2f position, float orientation);

	//GameObject methods
	void setup();
	void update(float deltaTime);
	void draw();

	// Boid Getter methods
	pRigidbody getRigidbody();
	_kinematicOutput * getKinematicInput();
	_dynamicOutput * getDynamicInput();
	ofVec2f getPosition();
	float getOrientation();
	float getBoidWidth();
	float getBoidRadius();

	// Boid Setter methods
	void SetPosition(ofVec2f i_position);
	void SetOrientation(float i_orientation);
	void SetColor(ofColor i_color);

	void setKinematicInput(kinematicOutput input);
	void setDynamicInput(dynamicOutput input);

	// Destructor
	~Boid();

};