#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	//ofLog(OF_LOG_NOTICE, "width: " + ofToString(screenWidth));

	ofWindowsHeight = ofGetWindowHeight();
	ofWindowsWidth = ofGetWindowWidth();

	float screenOffset = 16.0f;
	float offsetScreenWidth = ofGetWidth() - screenOffset;
	float  offsetScreenHeight = ofGetHeight() - screenOffset;

	ofSetBackgroundColor(255, 255, 255);

	// Black boid
	ofVec2f blackBoidStartCoordinate = { screenOffset, offsetScreenHeight };
	//ofVec2f blackBoidStartCoordinate = { ofGetWidth() / 3.0f, ofGetHeight() / 3.0f };
	float blackBoidStartOrientation = 4.71f;	// looking up
	blackBoid = new Boid(blackBoidStartCoordinate, blackBoidStartOrientation);
	boidGameObjects.push_back(blackBoid);


	// Red boid
	// redBoid start position in all other cases (for all dynamic movement algorithms)
	ofVec2f redBoidStartCoordinate = { ofGetWidth() / 2.0f, ofGetHeight() / 2.0f };
	float redBoidStartOrientation = 0.0f;
	redBoid = new Boid(redBoidStartCoordinate, redBoidStartOrientation);
	redBoid->SetColor(ofColor::red);
	boidGameObjects.push_back(redBoid);
	flockingBoids.push_back(redBoid);

	// Blue Boid
	ofVec2f blueBoidStartCoordinate = { ofGetWidth() / 2.0f + 10.0f, ofGetHeight() / 2.0f };
	float blueBoidStartOrientation = 0.0f;	// looking up
	blueBoid = new Boid(blueBoidStartCoordinate, blueBoidStartOrientation);
	blueBoid->SetColor(ofColor::blue);
	boidGameObjects.push_back(blueBoid);
	flockingBoids.push_back(blueBoid);

	// Green Boid
	ofVec2f greenBoidStartCoordinate = { ofGetWidth() / 2.0f, (ofGetHeight() / 2.0f) + 10.0f };
	float greenBoidStartOrientation = 0.0f;
	greenBoid = new Boid(greenBoidStartCoordinate, greenBoidStartOrientation);
	greenBoid->SetColor(ofColor::darkGreen);
	boidGameObjects.push_back(greenBoid);
	flockingBoids.push_back(greenBoid);

	// Pink Boid
	ofVec2f pinkBoidStartCoordinate = { (ofGetWidth() / 2.0f) - 10.0f, ofGetHeight() / 2.0f };
	float pinkBoidStartOrientation = 0.0f;
	pinkBoid = new Boid(pinkBoidStartCoordinate, pinkBoidStartOrientation);
	pinkBoid->SetColor(ofColor::hotPink);
	boidGameObjects.push_back(pinkBoid);
	flockingBoids.push_back(pinkBoid);

	// Black Boid Target
	ofVec2f blackBoidTargetStartCoordinate = { screenOffset, screenOffset };
	float blackBoidTargetStartOrientation = 0.0f;	// looking up
	blackBoidTarget = new Boid(blackBoidTargetStartCoordinate, blackBoidTargetStartOrientation);

	basicMotion = new BasicMotion(blackBoid->getRigidbody(), blackBoidTarget->getRigidbody(), 150.0f, blackBoidStartCoordinate, offsetScreenWidth, offsetScreenHeight,
		screenOffset);

	dynamicSeek = new DynamicSeek(blackBoid->getRigidbody(), redBoid->getRigidbody(), blackBoid->maxAccelerationMagnitude);

	float slowRadius = 200.0f;
	float targetRadius = 75.0f;
	float timeToDesiredVelocity = 0.001f;

	dynamicArrive = new DynamicArrive(blackBoid->getRigidbody(), redBoid->getRigidbody(), blackBoid->maxAccelerationMagnitude, blackBoid->maxSpeed,
		slowRadius, targetRadius, timeToDesiredVelocity);

	float slowAngle = glm::pi<float>() / 8;
	float targetAngle = slowAngle / 50;
	float timeToDesiredRotation = 0.0001f;

	dynamicLookForBlackBoid = new DynamicLookWhereYouAreGoing(blackBoid->getRigidbody(), blackBoid->maxAngularAccelerationMagnitude,
		blackBoid->maxAngularSpeed, slowAngle, targetAngle, timeToDesiredRotation);

	dynamicFaceForBlackBoid = new DynamicFace(blackBoid->getRigidbody(), redBoid->getRigidbody(), blackBoid->maxAngularAccelerationMagnitude,
		blackBoid->maxAngularSpeed, slowAngle, targetAngle, timeToDesiredRotation);

	float wanderRadius = 1000.0f;
	float closeRadius = 100.0f;

	dynamicWander = new DynamicWander(blackBoid->getRigidbody(), blackBoidTarget->getRigidbody(), blackBoid->maxAccelerationMagnitude, wanderRadius, closeRadius);

	float repulsionForceCoefficient = 1000000.0f;
	float personalSpaceRadius = 50.0f;

	dynamicEvade = new DynamicEvade(blackBoid->getRigidbody(), redBoid->getRigidbody(), blackBoid->maxAccelerationMagnitude, repulsionForceCoefficient, personalSpaceRadius);

	float maxPredictionTime = 0.001f;

	dynamicPursue = new DynamicPursue(redBoid->getRigidbody(), blackBoid->getRigidbody(), redBoid->maxAccelerationMagnitude, maxPredictionTime);

	// seek and look where you are going
	seekAndLook = new DynamicBlendedBehavior(blackBoid->maxAccelerationMagnitude, blackBoid->maxAngularAccelerationMagnitude);
	seekAndLook->addWeightedDynamicBehavior(dynamicSeek, 1.0f);
	seekAndLook->addWeightedDynamicBehavior(dynamicLookForBlackBoid, 1.0f);

	// arrive and look where you are going
	arriveAndLook = new DynamicBlendedBehavior(blackBoid->maxAccelerationMagnitude, blackBoid->maxAngularAccelerationMagnitude);
	arriveAndLook->addWeightedDynamicBehavior(dynamicArrive, 1.0f);
	arriveAndLook->addWeightedDynamicBehavior(dynamicLookForBlackBoid, 1.0f);

	// wander and look
	wanderAndLook = new DynamicBlendedBehavior(blackBoid->maxAccelerationMagnitude, blackBoid->maxAngularAccelerationMagnitude);
	wanderAndLook->addWeightedDynamicBehavior(dynamicWander, 1.0f);
	wanderAndLook->addWeightedDynamicBehavior(dynamicLookForBlackBoid, 1.0f);

	// wander and face
	wanderAndFace = new DynamicBlendedBehavior(blackBoid->maxAccelerationMagnitude, blackBoid->maxAngularAccelerationMagnitude);
	wanderAndFace->addWeightedDynamicBehavior(dynamicWander, 1.0f);
	wanderAndFace->addWeightedDynamicBehavior(dynamicFaceForBlackBoid, 1.0f);

	// evade and face
	evadeAndFace = new DynamicBlendedBehavior(blackBoid->maxAccelerationMagnitude, blackBoid->maxAngularAccelerationMagnitude);
	evadeAndFace->addWeightedDynamicBehavior(dynamicEvade, 1.0f);
	evadeAndFace->addWeightedDynamicBehavior(dynamicFaceForBlackBoid, 1.0f);

	// pursue only (red pursuing black)
	pursueOnly = new DynamicBlendedBehavior(redBoid->maxAccelerationMagnitude, redBoid->maxAngularAccelerationMagnitude);
	pursueOnly->addWeightedDynamicBehavior(dynamicPursue, 1.0f);

	// ================================================================================================================================================
	// FLOCKING BEHAVIOR SETUP

	dynamicFlocking = new DynamicFlocking(&flockingBoids, blackBoid, slowRadius, targetRadius, timeToDesiredVelocity,
		repulsionForceCoefficient, personalSpaceRadius, slowAngle, targetAngle, timeToDesiredRotation);

	// Stores the very first crumb's position   
	crumb.push_back(blackBoidStartCoordinate);
}

//--------------------------------------------------------------
void ofApp::update() {
	double deltaTime = ofGetLastFrameTime();

	dynamicFlocking->UpdateFlockingBehaviors();

	if (blackBoid != NULL) {
#pragma region Kinematic Updates - Basic Motion
		//blackBoid->setKinematicInput(basicMotion->getKinematicSteering());
#pragma endregion

#pragma region Dynamic Updates
//blackBoid->setDynamicInput(seekAndLook->getDynamicSteering());
//blackBoid->setDynamicInput(arriveAndLook->getDynamicSteering());
		blackBoid->setDynamicInput(wanderAndLook->getDynamicSteering());
		//blackBoid->setDynamicInput(wanderAndFace->getDynamicSteering());
		//blackBoid->setDynamicInput(evadeAndFace->getDynamicSteering());
#pragma endregion

#pragma region Crumb Spawning Logic
		ofVec2f lastCrumbPosition = crumb.back();

		// Ensures each crumb is separated by 20 units 
		if ((lastCrumbPosition - blackBoid->getPosition()).length() >= 20.0f) {
			crumb.push_back(blackBoid->getPosition());
		}

		// Longest chain of crumbs before they start getting cleaned up
		if (crumb.size() > 15)
			crumb.erase(crumb.begin());

#pragma endregion
	}

	// specific target behaviors update
	if (redBoid != NULL) {
		//redBoid->setDynamicInput(pursueOnly->getDynamicSteering());
	}

	for (vector<Boid*>::iterator itr = begin(boidGameObjects); itr != end(boidGameObjects); ++itr)
	{
		Boid * boid = *itr;

		if (boid != NULL) {
			boid->update(deltaTime);
		}
	}
}

void ClampToToroidalWorld(Boid * boid, float areaWidth, float areaHeight, float offset) {

	// if boid goes out the right side bring them in from the left
	if (boid->getPosition().x > (areaWidth + offset))
		boid->SetPosition(ofVec2f(-offset, boid->getPosition().y));
	// if boid goes out the left side bring them in from the right
	if (boid->getPosition().x < -offset)
		boid->SetPosition(ofVec2f(areaWidth + offset, boid->getPosition().y));
	// if boid goes out the bottom side bring them in from the top
	if (boid->getPosition().y > (areaHeight + offset))
		boid->SetPosition(ofVec2f(boid->getPosition().x, -offset));
	// if boid goes out the top side bring them in from the bottom
	if (boid->getPosition().y < -offset)
		boid->SetPosition(ofVec2f(boid->getPosition().x, areaHeight + offset));
}

//--------------------------------------------------------------
void ofApp::draw() {

	// brown color for crumbs
	ofSetColor(ofColor(165, 42, 42));
	for (int i = 0; i < crumb.size(); i++) {
		ofDrawCircle(crumb[i].x, crumb[i].y, 8);
	}

	// Toroidal world implementation for all boids in the world
	for (int i = 0; i < boidGameObjects.size(); i++) {
		Boid * boid = boidGameObjects[i];
		if (boid != NULL) {
			ClampToToroidalWorld(boid, ofWindowsWidth, ofWindowsHeight, boid->getBoidWidth());

			boid->draw();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (blackBoid->getKinematicInput()->velocity == ofVec2f::zero() && allowMouseInput)
	{
		ofVec2f clickPosition = ofVec2f((float)x, (float)y);
		redBoid->SetPosition(clickPosition);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
