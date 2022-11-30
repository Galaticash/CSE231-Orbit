/***********************************************************************
 * Header File:
 *    CollisionObject : An object in the orbital simulator that has collision.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Deals with any object that has collision. Detects collisions, deletes 
 *		object, and creates new ones when applicable. Earth is included because 
 *		it can collide even though it is not destroyed.
 ************************************************************************/
#pragma once
#include "object.h"
//#include "random.h"

class Simulator;

/*********************************************
 * Collision Object
 * An object that has collision.
 *********************************************/
class CollisionObject : public Object
{
public:
	CollisionObject(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Object(pos, vel, angle) 
	{ 
		this->radius = 0.0; 
		this->destroyed = false; 
		this->numFragments = 0; 
	};

	virtual void update(double time, double gravity, double planetRadius) {			
		// If the object has not collided,
		if (!destroyed) // TODO: this line technically doesn't have to be here, assert instead?
		{
			// Update normally
			Object::update(time, gravity, planetRadius);
		}
	}

	bool isHit(const CollisionObject &other) {
		double pixelsBetween = this->pos.pixelsBetween(other.pos);
		
		// TODO: Prevent destroy from being reset to false
		// ERROR: This line causes a crash,
		// if (distanceBetween <= other.radius + this->radius) { this->destroyed = true; }

		this->destroyed = pixelsBetween <= other.radius + this->radius;
		return this->destroyed;
	};

	// Getters and setters
	void setDestroyed(bool destroy) { this->destroyed = destroy; }; // Simulator will check for collisions
	virtual bool getDestroyed() { return this->destroyed; };

	// Normal Collision Objects will breakApart through deletion
	// And remove itself from the Simulator's list of Collision Objects
	// Given a list of additional Collision Objects that this Collision Object will break apart into, otherwise assumes none
	virtual void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {});
	
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