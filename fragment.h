#pragma once

#include "collisionObject.h"

/*********************************************
 * Fragment
 * A piece from a destroyed satellite or a destroyed part.
 * Small enough to eventually burn up and be deleted from 
 * the simulation.
 *********************************************/
class Fragment : public CollisionObject
{
public:
   Fragment(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CollisionObject(pos, vel, angle) { this->lifetime = 50; this->radius = 2; /*Lifetime is 50-100 frames*/ };

   bool isExpired() { if (lifetime <= 0) return true; else { lifetime--; return false; } }
   
   void update(double time = 0.0, double gravity = 0.0, double radius = 0.0) {
      if (isExpired())
      {
         this->destroyed = true; // The object is to be destroyed
      }
      else
         CollisionObject::update(time, gravity, radius);
   }
   void breakApart(Simulator* sim);

protected:
   int lifetime;
};