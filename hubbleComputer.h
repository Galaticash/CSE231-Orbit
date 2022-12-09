/***********************************************************************
 * Header File:
 *    Hubble Computer : A part in the orbital simulator that is created
 *    from a destroyed Hubble satellite.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    The Hubble computer has a radius of 7 and creates 2 fragments
 *    when destroyed.
 ************************************************************************/
#pragma once
#include "part.h"

/*********************************************
* HUBBLE COMPUTER
* A type of part in the orbit simulator.
*********************************************/
class HubbleComputer : public Part
{
public:
   HubbleComputer(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {
      this->radius = 7; // Radius in pixels
      this->numFragments = 2;
   };
};