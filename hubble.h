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
   Hubble(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Satellite(pos, vel, angle) {};
   void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {}) {
      
      // Add all the Fragments (from numFragments), 
      //  add them to the simulator, then delete self
      Satellite::breakApart(sim, { new HubbleComputer(), new HubbleTelescope(), new HubbleLeft(), new HubbleRight() });
   }
};