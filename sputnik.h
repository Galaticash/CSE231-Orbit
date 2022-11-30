/***********************************************************************
 * Header File:
 *    Sputnik : A satellite in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Sputnik has a radius of 4 and creates 0 parts and 4 fragments when destroyed.
 *    It starts at (-36,515,095.13, 21,082,000.0) and has a velocity of 
 *    (2,050.0, 2684.68).
 ************************************************************************/
#pragma once
#include "satellite.h"

/*********************************************
 * Sputnik
 * A type of Satellite in the orbit Simulator.
 * The only type of Satellite without subparts
 *********************************************/
class Sputnik : public Satellite
{
public:
   Sputnik(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Satellite(pos, vel, angle) 
   {
      this->radius = 4; // Radius in pixels
      this->numFragments = 4;
   };
};
