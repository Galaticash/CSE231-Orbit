#pragma once
/*********************************************
 * Collision Object
 * A fragment that is spawned in front of the spaceship.
 *********************************************/

#include "object.h"

class CollisionObject : public Object
{
public:
   // Constructors
   //CollisionObject() : CollisionObject(Position()) {};
   //CollisionObject(Position position) : CollisionObject(position, Velocity()) {};
   //CollisionObject(Position pos, Velocity vel) : CollisionObject(pos, vel, 0.0) {};
   //CollisionObject(Position pos, Velocity vel, double angle) : Object(pos, vel, angle) { this->radius = 0.0; };
  // Or
   CollisionObject(Position pos = Position(), Velocity vel = Velocity(), double angle = 0.0) : Object(pos, vel, angle) { this->radius = 0.0; };


   bool collided(CollisionObject otherObject) { return true; }

   double getRadius() { return radius; }

private:
   double radius;

};