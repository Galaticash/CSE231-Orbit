/***********************************************************************
 * Header File:
 *    Starlink Body : A part in the orbital simulator that is created
 *    from a destroyed Starlink satellite.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    The Starlink body has a radius of 2 and creates 3 fragments 
 *    when destroyed.
 ************************************************************************/
#pragma once
#include "part.h"

/*********************************************
* STARLINK BODY
* A type of part in the orbit simulator.
*********************************************/
class StarlinkBody : public Part
{
public:
   StarlinkBody(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {
      this->radius = 2; // Radius in pixels
      this->numFragments = 3;
   };
};