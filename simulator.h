#pragma once

#include "spaceship.h"
#include "star.h"
#include "earth.h"

class Simulator {
public:
	Simulator()
	{
		this->Ship = new Spaceship();
		addCollider(Ship); // Add to the list of Collision Objects
		addCollider(new Earth()); // Create an Earth and add it to the list of Collision Objects
	
	};
	void createStars() { /* For numStars, add new Star() to list of Stars */ };
	void addCollider(CollisionObject* newObj) { this->collisionObjects.push_back(newObj); };

	vector<Pixel>* getVisuals() { vector<Pixel> empty; return &empty; };


private:
	vector<CollisionObject*> collisionObjects;
	Spaceship* Ship;
	vector<Star> stars;

};