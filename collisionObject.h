

#pragma once

#include "object.h"

/*********************************************
 * Collision Object
 * A fragment that is spawned in front of the spaceship.
 *********************************************/
class CollisionObject : public Object
{
public:
   // Constructors
   CollisionObject() : CollisionObject(Position()) {};
   CollisionObject(Position position) : CollisionObject(position, Velocity()) {};
   CollisionObject(Position pos, Velocity vel) : Object(pos, vel) { this->radius = 0.0; };


   bool collided(CollisionObject otherObject) { return true; }

   double getRadius() { return radius; }

private:
   double radius;

};