#pragma once
#include "satellite.h"

// Starlink subparts
#include "StarlinkBody.h"
#include "StarlinkArray.h"

/*********************************************
 * Starlink
 * A type of satellite in the orbit simulator.
 *********************************************/
class Starlink : public Satellite
{
public:
   Starlink(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Satellite(pos, vel, angle)
   {   
      this->radius = 6; // Radius in pixels;
      this->numFragments = 2;
   };

   void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {}) {

      // Add all the Fragments (from numFragments), 
      //  add them to the simulator, then delete self
      Satellite::breakApart(sim, { new StarlinkBody(), new StarlinkArray() });
   }
};