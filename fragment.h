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
   Fragment(Position pos = Position(), Velocity vel = Velocity(), double angle = 0.0) : CollisionObject(pos, vel, angle) { this->lifetime = 0; };

   bool isExpired() { return true; }

private:
   int lifetime;
};