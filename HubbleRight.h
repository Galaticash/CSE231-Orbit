/***********************************************************************
 * Header File:
 *    Hubble Right : A part in the orbital simulator that is created
 *    from a destroyed Hubble satellite.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    The Hubble right has a radius of 8 and creates 2 fragments
 *    when destroyed.
 ************************************************************************/
#pragma once
#include "part.h"

class HubbleRight : public Part
{
public:
   HubbleRight(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {
      this->radius = 8; // Radius in pixels
      this->numFragments = 2;
   };
   /*private:
      createVisual()*/
};