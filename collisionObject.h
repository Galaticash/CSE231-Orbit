

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
   CollisionObject();

   bool collided(CollisionObject otherObject) { return true; }

   double getRadius() { return radius; }

private:
   double radius;
   
};