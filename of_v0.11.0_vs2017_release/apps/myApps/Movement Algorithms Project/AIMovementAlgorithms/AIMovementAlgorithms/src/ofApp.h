#pragma once

#include "ofMain.h"
#include "Boid.h"

#include "BasicMotion.h"
#include "DynamicSeek.h"
#include "DynamicFlee.h"
#include "DynamicArrive.h"
#include "DynamicAlign.h"
#include "DynamicVelocityMatch.h"
#include "DynamicWander.h"
#include "DynamicPursue.h"
#include "DynamicEvade.h"
#include "DynamicSeparation.h"
#include "DynamicLookWhereYouAreGoing.h"
#include "DynamicFace.h"
#include "DynamicBlendedBehavior.h"
#include "DynamicFlocking.h"

#include <vector>

class ofApp : public ofBaseApp {

	Boid * blackBoid = NULL;

	Boid * redBoid = NULL;
	Boid * blueBoid = NULL;
	Boid * greenBoid = NULL;
	Boid * pinkBoid = NULL;

	Boid * blackBoidTarget = NULL;

	vector<Boid*> boidGameObjects;
	vector<Boid*> flockingBoids;

	vector<ofVec2f> crumb;

	rigidbody offscreenTarget;

	// Basic Kinematic Movement Algorithms
	BasicMotion * basicMotion = NULL;

	// Basic Dynamic Movement Algorithms
	DynamicSeek * dynamicSeek = NULL;
	DynamicFlee * dynamicFlee = NULL;
	DynamicArrive * dynamicArrive = NULL;
	DynamicAlign * dynamicAlign = NULL;
	DynamicVelocityMatch * dynamicVelocityMatch = NULL;


	// Advanced Dynamic Movement Algorithms
	DynamicWander * dynamicWander = NULL;
	DynamicPursue * dynamicPursue = NULL;
	DynamicEvade * dynamicEvade = NULL;
	DynamicSeparation * dynamicSeparation = NULL;
	DynamicLookWhereYouAreGoing * dynamicLookForBlackBoid = NULL;
	DynamicFace * dynamicFaceForBlackBoid = NULL;
	DynamicFlocking * dynamicFlocking = NULL;

	DynamicBlendedBehavior * seekAndLook = NULL;
	DynamicBlendedBehavior * arriveAndLook = NULL;
	DynamicBlendedBehavior * evadeAndLook = NULL;
	DynamicBlendedBehavior * pursueOnly = NULL;
	DynamicBlendedBehavior * wanderAndLook = NULL;
	DynamicBlendedBehavior * wanderAndFace = NULL;
	DynamicBlendedBehavior * evadeAndFace = NULL;

	// Window dimensions
	float ofWindowsHeight;
	float ofWindowsWidth;
	int windowXmax;
	int windowXmin;
	int windowYmax;
	int windowYmin;

	bool allowMouseInput = false;

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

};
