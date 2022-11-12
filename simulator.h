#pragma once

#include "spaceship.h"
#include "star.h"
#include "earth.h"

// Simulation Information
const double TIME = 48;         // Real-world seconds between frames

// TODO: Move these to Earth, and pass that to update (only gravitational item affecting others)
const double GRAVITY = -9.8067;           // Gravity constant in m/s^2
const double EARTH_RADIUS = 6378000.0;    // meters

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

	void moveShip(double x, double y);

	// Given an amount of time (seconds), update all collision objects
	// Defaults to the assumed 48 seconds per frames if no values given
	void update(double t = TIME, bool gravityOn = true)
	{
		// TODO: Pass Earth/Earth varaibles to objects?, tell them what is affecting their movement (gravity of Earth at position)
		// TODO: Check for collisions between CollisionObjects
		// TODO: Update all the Stars (what frame they are on/movement)

		// Update the position of each Object (all other objects are CollisionObjects
		for (vector<CollisionObject*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
		{
			CollisionObject* obj = *it;

			// If gravity is turned off, passes 0 values
			double gravity = gravityOn ? GRAVITY : 0.0;
			double radius = gravityOn ? EARTH_RADIUS : 0.0;
			obj->update(t, gravity, radius);

			// TODO: If an object has been hit...
			// If it has parts/particles to create/break into,
			// Make those parts, insert into collisionObjects, each going a different direction
		}
	}

	vector<Object*> getObjects(); // Get all Objects to be drawn

protected:
	vector<CollisionObject*> collisionObjects;
	Spaceship* Ship;
	vector<Star> stars;
	double timeDialation;

};