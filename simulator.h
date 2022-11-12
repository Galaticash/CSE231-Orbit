#pragma once

#include "spaceship.h"
#include "star.h"
#include "earth.h"


//const double GRAVITY = -9.8067;           // Gravity constant in m/s^2
//const double EARTH_RADIUS = 6378000.0;    // meters

// Simulation Information
const double TIME = 48;         // Real-world seconds between frames

class Simulator {
public:
	Simulator()
	{
		this->Ship = new Spaceship(Position(35786000.0 + 6378000.0, 0.0), Velocity(0.0, 3100.0));
		addCollider(Ship); // Add to the list of Collision Objects
		addCollider(new Earth()); // Create an Earth and add it to the list of Collision Objects
	
	};
	void createStars() { /* For numStars, add new Star() to list of Stars */ };
	void addCollider(CollisionObject* newObj) { this->collisionObjects.push_back(newObj); };

	void moveShip(double x, double y) {};

	void update();
	vector<Object*> getObjects(); // Get all Objects to be drawn


private:
	vector<CollisionObject*> collisionObjects;
	Spaceship* Ship;
	vector<Star> stars;
	double timeDialation;

};