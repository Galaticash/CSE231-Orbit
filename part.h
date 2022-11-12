#pragma once
/*********************************************
 * Part
 * A piece of a destroyed satellite. Gets part of it's velocity
 * from the destroyed satellite.
 *********************************************/

#include "collisionObject.h"

class Part : CollisionObject
{
public:
   Part(Position pos = Position(), Velocity vel = Velocity(), double angle = 0.0) : CollisionObject(pos, vel, angle) { numFragments = 0; };

private:
   int numFragments;
};