#include "Boid.h"

Boid::Boid(ofVec2f position, float orientation)
{
	this->rigidbody.position = position;
	this->rigidbody.orientation = orientation;
	this->rigidbody.velocity = ofVec2f::zero();
	this->rigidbody.rotation = 0.0f;
	boidColor.r = 0;
	boidColor.g = 0;
	boidColor.b = 0;
}

void Boid::setup()
{
}

void Boid::update(float deltaTime)
{
	if (this->kinematicInput.velocity != ofVec2f::zero() ||
		this->kinematicInput.rotation != 0)
	{
		this->rigidbody.position += kinematicInput.velocity * deltaTime;
		this->rigidbody.orientation += kinematicInput.rotation * deltaTime;
	}


	// updating rigidbody position and orientation
	this->rigidbody.position += this->rigidbody.velocity * deltaTime;
	this->rigidbody.orientation += this->rigidbody.rotation * deltaTime;

	// updating rigidbody velocity and rotation
	this->rigidbody.velocity += dynamicInput.linear * deltaTime;
	this->rigidbody.rotation += dynamicInput.angular * deltaTime;


	// clamp to max angular speed
	if (fabs(this->rigidbody.rotation) > maxAngularSpeed) {
		this->rigidbody.rotation /= fabs(this->rigidbody.rotation);		// gets the sign of rotation
		this->rigidbody.rotation *= maxAngularSpeed;
	}

	// clamp to max speed
	if (this->rigidbody.velocity.length() > this->maxSpeed) {
		this->rigidbody.velocity.normalize();
		this->rigidbody.velocity *= this->maxSpeed;
	}

	// apply friction if in motion
	if (this->rigidbody.velocity.length() > 0) {
		float xSign = -glm::sign(this->rigidbody.velocity.x);
		float ySign = -glm::sign(this->rigidbody.velocity.y);
		ofVec2f friction = { xSign * 0.1f, ySign * 0.1f };
		
		this->rigidbody.velocity += friction;
	}

	if (abs(this->rigidbody.rotation) > 0) {
		this->rigidbody.rotation += (-(glm::sign(this->rigidbody.rotation)) * 1.5f);
	}
}

void Boid::draw()
{
	ofPushMatrix();

	ofTranslate(rigidbody.position.x, rigidbody.position.y);
	ofRotateRad(rigidbody.orientation);

	// Boid color
	ofSetColor(boidColor);

	// Boid body
	ofDrawCircle(0, 0, radius);

	// Boid beak
	float x1 = 0;
	float x2 = 0;
	float x3 = width;
	float y1 = -radius;
	float y2 = radius;
	float y3 = 0;
	ofDrawTriangle(x1, y1, x2, y2, x3, y3);

	ofPopMatrix();
}

void Boid::setKinematicInput(kinematicOutput input)
{
	this->kinematicInput = input;
}

void Boid::setDynamicInput(dynamicOutput input) 
{
	this->dynamicInput = input;
}

pRigidbody Boid::getRigidbody()
{
	return &(this->rigidbody);
}

_kinematicOutput * Boid::getKinematicInput()
{
	return &(this->kinematicInput);
}

_dynamicOutput * Boid::getDynamicInput()
{
	return &(this->dynamicInput);
}

ofVec2f Boid::getPosition()
{
	return this->rigidbody.position;
}

float Boid::getOrientation()
{
	return this->rigidbody.orientation;
}

float Boid::getBoidWidth()
{
	return this->width;
}

float Boid::getBoidRadius()
{
	return this->radius;
}

void Boid::SetPosition(ofVec2f i_position)
{
	this->rigidbody.position = i_position;
}

void Boid::SetOrientation(float i_orientation)
{
	this->rigidbody.orientation = i_orientation;
}

void Boid::SetColor(ofColor i_color)
{
	this->boidColor = i_color;
}


Boid::~Boid()
{
	/*boidColor.r = 1;
	boidColor.g = 1;
	boidColor.b = 1;*/
}