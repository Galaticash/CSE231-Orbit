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
   Fragment(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CollisionObject(pos, vel, angle) { this->lifetime = 0; this->radius = 2; };

   bool isExpired() { return true; }
   void breakApart(Simulator* sim);

protected:
   int lifetime;
};