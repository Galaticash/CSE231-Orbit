#pragma once

#include "spaceship.h"
#include "star.h"
#include "earth.h"
#include "bullet.h"

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
	void removeCollider(CollisionObject* removeObj) { 
		// If the given pointer is in the vector, remove it
		vector<CollisionObject*>::iterator removeIt = find(collisionObjects.begin(), collisionObjects.end(), removeObj);
		if (removeIt != collisionObjects.end())
		{
			//delete* removeIt;
			this->collisionObjects.erase(removeIt);
		}
	};

	void createBullet(Position pos, Velocity vel, double angle) {};
	void moveShip(double x, double y);

	// Given an amount of time (seconds), update all collision objects
	// Defaults to the assumed 48 seconds per frames if no values given
	void update(double t = TIME, bool gravityOn = true)
	{
		vector<CollisionObject*> colliders;

		// TODO: Pass Earth/Earth varaibles to objects?, tell them what is affecting their movement (gravity of Earth at position)
		// Check for collisions between CollisionObjects
		for (vector<CollisionObject*>::iterator objOneIt = this->collisionObjects.begin(); objOneIt != this->collisionObjects.end(); objOneIt++)
		{
			// Check against every object except itself
			for (vector<CollisionObject*>::iterator objTwoIt = objOneIt + 1; objTwoIt != this->collisionObjects.end(); objTwoIt++)
			{
				// If an Object has been hit, set collided of other object to true
				//assert((*objOneIt) != (*objTwoIt));
				if ((*objOneIt)->isHit(*(*objTwoIt)))
				{
					// Tell the second object it was hit
					(*objTwoIt)->setCollided(true);

					// TODO: Check if in collisions list already

					// Add both objects to the list of colliding objects
					colliders.push_back(*objOneIt);
					colliders.push_back(*objTwoIt);
				}
			}
		}

		// For every object that collided,
		for (vector<CollisionObject*>::iterator it = colliders.begin(); it != colliders.end(); it++)
		{
			// Break the object apart, adding subParts to the Simulator's list of collisionObjects
			CollisionObject* obj = *it;
			obj->breakApart(this);
		}
		colliders.clear();

		// TODO: Update all the Stars (what frame they are on/movement)
		/*for (vector<Star*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
		{

		}*/

		// Update the position of each CollisionObject
		for (vector<CollisionObject*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
		{
			CollisionObject* obj = *it;

			// If gravity is turned off, passes 0 values
			double gravity = gravityOn ? GRAVITY : 0.0;
			double radius = gravityOn ? EARTH_RADIUS : 0.0;
			obj->update(t, gravity, radius);
		}
	}

	vector<Object*> getObjects(); // Get all Objects to be drawn

protected:
	vector<CollisionObject*> collisionObjects;
	Spaceship* Ship;
	vector<Star> stars;
	double timeDialation;
};
