/***********************************************************************
 * Header File:
 *    Starlink Array : A part in the orbital simulator that is created
 *    from a destroyed Starlink satellite.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    The Starlink array has a radius of 4 and creates 3 fragments
 *    when destroyed.
 ************************************************************************/
#pragma once
#include "part.h"

class StarlinkArray : public Part
{
public:
   StarlinkArray(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {
      this->radius = 4; // Radius in pixels
      this->numFragments = 3;
   };
};