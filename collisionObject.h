#pragma once

#include "object.h"

class Simulator;

/*********************************************
 * Collision Object
 * A fragment that is spawned in front of the spaceship.
 *********************************************/
class CollisionObject : public Object
{
public:
	CollisionObject(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Object(pos, vel, angle) { this->radius = 0.0; this->destroyed = false; this->numFragments = 0; };

	virtual void update(double time, double gravity = 0.0, double planetRadius = 0.0) {			
		// If the object has not collided,
		if (!destroyed)
		{
			// Calculate normally
			Object::update(time, gravity, planetRadius);
		}
	}

	bool isHit(const CollisionObject &other) {
		double distanceBetween = this->pos.distanceBetween(other.pos);
		// Only one change and it breaks, trying to solve destroy -> false possible error
		// if (distanceBetween <= other.radius + this->radius) { this->destroyed = true; }

		this->destroyed = distanceBetween <= other.radius + this->radius;
		return this->destroyed;
	};

	// Getters and setters
	void setDestroyed(bool destroy) { this->destroyed = destroy; }; // Simulator will check for collisions
	virtual bool getDestroyed() { return this->destroyed; };

	// Normal Collision Objects will breakApart through deletion
	// And remove itself from the list
	virtual void breakApart(Simulator* sim);
	
	int getNumFragments() const { return this->numFragments; };

   double getRadius() const { return radius; };

protected:
	void addObjects(Simulator* sim, vector<CollisionObject*> obj);

	vector<Velocity> getSubPartVel(int subParts);
	vector<Position> getSubPartPos(vector<Velocity> directions);

	bool destroyed;     // If the current Object is to be destroyed (from a collision or timer expiring)
   double radius;      // How large this object is, used to check if another object is touching it
	int numFragments;   // The number of fragments this object will break into
};