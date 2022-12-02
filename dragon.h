/***********************************************************************
 * Header File:
 *    Dragon : A satellite in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Dragon has a radius of 7 and creates 3 parts and 2 fragments when destroyed.
 *    It starts at (0.0, 8,000,000.0) and has a velocity of (-7,900.0, 0.0).
 ************************************************************************/
#pragma once
#include "satellite.h"

// Dragon parts
#include "dragonCenter.h"
#include "dragonLeft.h"
#include "dragonRight.h"

/*********************************************
 * Dragon
 * A type of satellite in the orbit simulator.
 *********************************************/
class Dragon : Satellite
{
public:
   Dragon(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Satellite(pos, vel, angle)
   {
      this->radius = 12; // Radius in pixels;
      this->numFragments = 2;
   };

   void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {}) {

      // Add all the parts, 
      //  add them to the simulator, then delete self
      Satellite::breakApart(sim, { new dragonCenter, new dragonLeft(), new dragonRight() });
   }

};