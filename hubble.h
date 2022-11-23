#pragma once

#include "satellite.h"
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
   void breakApart(Simulator* sim)
   {
      vector<CollisionObject*> subParts = { new HubbleComputer(), new HubbleTelescope(), new HubbleLeft(), new HubbleRight() };

      // Add all Parts to the Simulator
      addObjects(sim, subParts);

      // Add all the Fragments, and delete itself
      CollisionObject::breakApart(sim);   
   }
};