/***********************************************************************
 * Header File:
 *    Part : A collisionObject in the orbital simulator that is created from 
 *    destroyed satellites. Can be destroyed and break apart into fragments.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    A piece of a whole that is given a random speed and angle within a
 *    range from the satellite. The number of fragments and radius 
 *    differ between parts.
 ************************************************************************/
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
   Part(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CollisionObject(pos, vel, angle)
   {
      this->numFragments = 0;
      this->radius = 1; // Radius in pixels
   };
};