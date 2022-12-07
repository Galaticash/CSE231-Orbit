/***********************************************************************
 * Header File:
 *    Hubble Left : A part in the orbital simulator that is created
 *    from a destroyed Hubble satellite.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    The Hubble left has a radius of 8 and creates 2 fragments
 *    when destroyed.
 ************************************************************************/
#pragma once
#include "part.h"

/*********************************************
* HUBBLE LEFT
* A type of part in the orbit simulator.
*********************************************/
class HubbleLeft : public Part
{
public:
   HubbleLeft(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {
      this->radius = 8; // Radius in pixels
      this->numFragments = 2;
   };
};