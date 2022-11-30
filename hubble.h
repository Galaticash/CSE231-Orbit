/***********************************************************************
 * Header File:
 *    Hubble : A satellite in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Hubble has a radius of 10 and creates 4 parts and 0(2?) fragments when destroyed.
 *    It starts at (0.0, -42,164,000.0) and has a velocity of (3,100.0, 0.0).
 ************************************************************************/
#pragma once
#include "satellite.h"

// Hubble subparts
#include "hubbleComputer.h"
#include "hubbleTelescope.h"
#include "hubbleLeft.h"
#include "hubbleRight.h"

/*********************************************
 * Hubble
 * A type of satellite in the orbit simulator.
 *********************************************/
class Hubble : public Satellite
{
public:
   Hubble(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Satellite(pos, vel, angle) 
   {
      this->radius = 10; // Radius in pixels;
      this->numFragments = 0;
   };

   void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {}) {
      
      // Add all the Fragments (from numFragments), 
      //  add them to the simulator, then delete self
      Satellite::breakApart(sim, { new HubbleComputer(), new HubbleTelescope(), new HubbleLeft(), new HubbleRight() });
   }
};