/***********************************************************************
 * Header File:
 *    Dragon Center : A part in the orbital simulator that is created
 *    from a destroyed Hubble satellite.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    The Hubble left has a radius of 6 and creates 4 fragments
 *    when destroyed.
 ************************************************************************/
#pragma once
#include "part.h"

class DragonCenter : public Part
{
public:
   DragonCenter(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {
      this->radius = 6; // Radius in pixels
      this->numFragments = 4;
   };
};