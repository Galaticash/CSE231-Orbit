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

#include <vector>  // To hold subparts

class Simulator; // To use in breakApart

/*********************************************
 * Collision Object
 * An Object that can collide with other Collision Objects
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

   /******************************************
   * UPDATE
   * Asserts destroyed Collision Objects aren't updated
   * Updates the same as a normal Object
   ********************************************/
   virtual void update(double time, double gravity, double planetRadius) {
      // A collided Object should be destroyed before updating
      assert(!destroyed);

      // Update the same as a normal Object (Position, Velocity, etc)
      Object::update(time, gravity, planetRadius);
   }

   /******************************************
   * IS HIT
   * Checks if this Collision Object has come
   * in contact with a given Collision Object
   ********************************************/
   bool isHit(const CollisionObject& other);

   // Getters and setters
   void setDestroyed(bool destroy) { this->destroyed = destroy; };
   virtual bool getDestroyed() { return this->destroyed; };

   int getNumFragments() const { return this->numFragments; };
   double getRadius() const { return radius; };
	 
   /******************************************
   * BREAK APART
   * Creates fragments after a collision and has them
   * added to the simulator's list of objects.
   ********************************************/
   virtual void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {});

protected: 
   /******************************************
   * ADD OBJECTS
   * Given the Simulator and Collision Objects to add,
   * adds the subParts to the Simulator's Collision Objects
   ********************************************/
   void addObjects(Simulator* sim, vector<CollisionObject*> subParts);

   /******************************************
   * GET SUB PART VELOCITY
   * Calculates the Velocity of created subParts
   * given the total number of Parts and Fragments.
   ********************************************/
   vector<Velocity> getSubPartVel(int subParts);
	
   /******************************************
   * GET SUB PART POSITION
   * Calculates the Position of created subParts
   * given the total number of Parts and Fragments.
   ********************************************/
   vector<Position> getSubPartPos(vector<Velocity> directions);

   bool destroyed;     // If the current Object is to be destroyed (either from a collision or timer expiring)
   double radius;      // How large this object is, used to check if another object is touching it
   int numFragments;   // The number of fragments this object will break into
};
