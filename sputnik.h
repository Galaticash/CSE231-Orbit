#pragma once
#include "satellite.h"

// Sputnik has no subparts

/*********************************************
 * Sputnik
 * A type of satellite in the orbit simulator.
 *********************************************/
class Sputnik : public Satellite
{
public:
   Sputnik(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Satellite(pos, vel, angle) {};
   
   /*void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {}) {

      // Add all the Fragments (from numFragments), 
      //  add them to the simulator, then delete self
      Satellite::breakApart(sim, {});
   }*/
};
