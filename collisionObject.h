#pragma once
/*********************************************
 * Collision Object
 * A fragment that is spawned in front of the spaceship.
 *********************************************/

#include "object.h"

class Simulator;

class CollisionObject : public Object
{
public:
	// Constructors
	//CollisionObject() : CollisionObject(Position()) {};
	//CollisionObject(Position position) : CollisionObject(position, Velocity()) {};
	//CollisionObject(Position pos, Velocity vel) : CollisionObject(pos, vel, 0.0) {};
	//CollisionObject(Position pos, Velocity vel, double angle) : Object(pos, vel, angle) { this->radius = 0.0; };
  // Or
	CollisionObject(Position pos = Position(), Velocity vel = Velocity(), double angle = 0.0) : Object(pos, vel, angle) { this->radius = 0.0; this->collided = false; this->numFragments = 0; };

	virtual void update(double time, double gravity = 0.0, double planetRadius = 0.0) {			
		// If the object has not collided,
		if (!collided)
		{
			// Calculate normally
			Object::update(time, gravity, planetRadius);
		}
		/*else
		{
			// If deleted in Simulator's update, interupts vector loop
			//breakApart();
		}*/
	}

	virtual void update(Simulator* sim);

	virtual bool isHit(const CollisionObject &other) {
		double distanceBetween = this->pos.distanceBetween(other.pos);
		this->collided = distanceBetween <= other.radius + this->radius;
		return this->collided;
	};

	// Getters and setters
	void setCollided(bool c) { this->collided = c; }; // Simulator will check for collisions
	bool getCollided() { return this->collided; };

	// Normal Collision Objects will breakApart through deletion
	// And remove itself from the list
	virtual void breakApart(Simulator* sim);
	
	virtual int getNumFragments() const { return this->numFragments; };

   virtual double getRadius() const { return radius; };

protected:
	void addObjects(Simulator* sim, vector<CollisionObject*> obj);

	vector<Velocity> getSubPartVel(int subParts);
	vector<Position> getSubPartPos(vector<Velocity> directions);


   bool collided;
   double radius;
	int numFragments;
};