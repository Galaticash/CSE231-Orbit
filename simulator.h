#pragma once

#include "spaceship.h"
#include "star.h"
#include "earth.h"
#include "bullet.h"

// Simulation Information
const double TIME = 48;         // Real-world seconds between frames

// TODO: Move these to Earth, and pass that to update (only gravitational item affecting others)
const double GRAVITY = -9.8067;           // Gravity constant in m/s^2

class Simulator {
public:
	Simulator()
	{
		this->ship = new Spaceship(Position(35786000.0 + 6378000.0, 0.0), Velocity(0.0, 3100.0));
		addCollider(ship); // Add to the list of Collision Objects
		this->planet = new Earth();
		addCollider(planet); // Create an Earth and add it to the list of Collision Objects
	};
	void createStars() { /* For numStars, add new Star() to list of Stars */ };
	void addCollider(CollisionObject* newObj) { this->collisionObjects.push_back(newObj); };
	void removeCollider(CollisionObject* removeObj) { 
		// If the given pointer is in the vector, remove it
		vector<CollisionObject*>::iterator removeIt = find(collisionObjects.begin(), collisionObjects.end(), removeObj);
		if (removeIt != collisionObjects.end())
		{
			//delete* removeIt; // Not in charge of deleting the object
			this->collisionObjects.erase(removeIt);
		}
	};

	void createBullet(Position pos, Velocity vel, Angle angle) {};
	void moveShip(double x, double y);

	// Given an amount of time (seconds), update all collision objects
	// Defaults to the assumed 48 seconds per frames if no values given
	void update(double t = TIME, bool gravityOn = true)
	{
		// TODO: Pass Earth/Earth varaibles to objects?, tell them what is affecting their movement (gravity of Earth at position)
		
		// Check for collisions between the Simulator's collisionObjects
		vector<CollisionObject*> colliders = getCollisions();

		// For every Collision Object that has collided,
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
			double radius = gravityOn ? planet->getRadius() : 0.0;

			obj->update(t, gravity, radius);
		}
	}

	vector<Object*> getObjects(); // Get all Objects to be drawn

protected:
	vector<CollisionObject*> collisionObjects;	// All Objects that can collide
	Spaceship* ship;	// The user-controlled Spaceship
	Earth* planet; // Could be modified to use different Planets
	vector<Star> stars;	// All the stars to display
	double timeDialation;


	vector<CollisionObject*> getCollisions() {
		vector<CollisionObject*> colliders;

		// For every Collison Object in the Simulator's collisionObjects,
		for (vector<CollisionObject*>::iterator objOneIt = this->collisionObjects.begin(); objOneIt != this->collisionObjects.end(); objOneIt++)
		{
			// Check against every object except itself
			for (vector<CollisionObject*>::iterator objTwoIt = objOneIt + 1; objTwoIt != this->collisionObjects.end(); objTwoIt++)
			{
				// Should never check collisions against self
				//assert((*objOneIt) != (*objTwoIt)); // TODO: assert not included

				// TODO: Change for odd number collisions? 3rd object
				// If neither object has been involved in a collision yet,
				if (!(*objOneIt)->getCollided() && !(*objTwoIt)->getCollided())
				{
					// Check if the two Objects have hit eachother,
					if ((*objOneIt)->isHit(*(*objTwoIt)))
					{
						// Tell the second object it was hit
						(*objTwoIt)->setCollided(true);

						// Add both objects to the list of colliding objects
						colliders.push_back(*objOneIt);
						colliders.push_back(*objTwoIt);
					}
				}
				else if ((!(*objOneIt)->getCollided() && (*objTwoIt)->getCollided()))
				{
					if ((*objOneIt)->isHit(*(*objTwoIt)))
					{
						// Add object to the list of colliding objects
						colliders.push_back(*objOneIt);
					}
				}
				else if ((!(*objTwoIt)->getCollided() && (*objOneIt)->getCollided()))
				{
					if ((*objTwoIt)->isHit(*(*objOneIt)))
					{
						// Add object to the list of colliding objects
						colliders.push_back(*objTwoIt);
					}
				}
			}
		}
		return colliders;
	};
};
