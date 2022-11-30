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
