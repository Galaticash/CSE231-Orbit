/***********************************************************************
 * Header File:
 *    GPS : A satellite in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    GPS has a radius of 12 and creates 3 parts and 2 fragments when destroyed.
 *    These remain in Geosynchronous orbit at a constant velocity. When 
 *    directly above the earth (0.0, 26,560,000.0), the velocity is (-3,880.0, 0.0).
 ************************************************************************/
#pragma once
#include "satellite.h"

/*********************************************
 * GPS
 * A type of satellite in the orbit simulator.
 *********************************************/
class GPS : Satellite
{
public:
   GPS(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Satellite(pos, vel, angle)
   {
      this->radius = 12; // Radius in pixels;
      this->numFragments = 2;
   };

private:

};
