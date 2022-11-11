

#pragma once

#include "collisionObject.h"

/*********************************************
 * Part
 * A piece of a destroyed satellite. Gets part of it's velocity
 * from the destroyed satellite.
 *********************************************/
class Part : CollisionObject
{
public:
   Part();

private:
   int numFragments;
};