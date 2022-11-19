#pragma once

#include "collisionObject.h"

/*********************************************
 * Part
 * A piece of a destroyed Satellite, 
 * created when a Satellite breaks apart. 
 * Gets part of it's velocity from the 
 * destroyed Satellite.
 *********************************************/
class Part : public CollisionObject
{
public:
   Part(Position pos = Position(), Velocity vel = Velocity(), double angle = 0.0) : CollisionObject(pos, vel, angle) { numFragments = 2; };
};