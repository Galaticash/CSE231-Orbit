/***********************************************************************
 * Header File:
 *    Hubble Telescope : A part in the orbital simulator that is created
 *    from a destroyed Hubble satellite.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    The Hubble telescope has a radius of 10 and creates 3 fragments
 *    when destroyed.
 ************************************************************************/
#pragma once
#include "part.h"

//string drawType = "hubbleTelescope";

/*********************************************
* HUBBLE TELESCOPE
* A type of part in the orbit simulator.
*********************************************/
class HubbleTelescope : public Part
{
public:
   HubbleTelescope(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {
      this->radius = 10; // Radius in pixels
      this->numFragments = 3;
   };
};