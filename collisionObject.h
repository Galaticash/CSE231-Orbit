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
#include "uiDraw.h"

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
		this->radius = 0; // The Collision Object's radius in Pixels
		this->numFragments = 0;
		this->destroyed = false; 
	};

	virtual void update(double time, double gravity, double planetRadius) {
		// A collided Object should be destroyed before updating
		assert(!destroyed);

		// Update the same as a normal Object (Position, Velocity, etc)
		Object::update(time, gravity, planetRadius);
	}

	// Checks if this Collision Object has hit a given Collision Object
	bool isHit(const CollisionObject& other);

	// Getters and setters
	void setDestroyed(bool destroy) { this->destroyed = destroy; }; // TODO: Not needed?
	virtual bool getDestroyed() { return this->destroyed; };

	int getNumFragments() const { return this->numFragments; }; // TODO: Not needed?
	double getRadius() const { return radius; };

	/* Normal Collision Objects will breakApart by removing itself
	 *  from the Simulator's list of Collision Objects and deleting itself.
	 *  Given a list of additional Collision Objects that this Collision Object 
	 *  will break apart into, otherwise assumes none */
	virtual void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {});

protected:
	// Given the Simulator, adds subParts to the Simulator's Collision Objects
	void addObjects(Simulator* sim, vector<CollisionObject*> obj);		

	vector<Velocity> getSubPartVel(int subParts);	// Calculates the Velocities of subparts
	vector<Position> getSubPartPos(vector<Velocity> directions);	// Calculates the initial Positions of subparts

	bool destroyed;     // If the current Object is to be destroyed (either from a collision or timer expiring)
   double radius;      // How large this object is, used to check if another object is touching it
	int numFragments;   // The number of fragments this object will break into
};