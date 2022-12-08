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


   /************************************************************************
 * DRAW Hubble
 * Draw a Hubble satellite on the screen. It consists of 4 parts
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
   /*
   void draw()
   {
      Position posTelescope;
      posTelescope.setPixelsX(2.0);
      posTelescope.setPixelsY(0.0);
      HubbleTelescope::draw();
      //drawHubbleTelescope(center, rotation, posTelescope);

      Position posComputer;
      posComputer.setPixelsX(-10.0);
      posComputer.setPixelsY(0.0);
      drawHubbleComputer(center, rotation, posComputer);

      Position posRight;
      posRight.setPixelsX(1.0);
      posRight.setPixelsY(-8.0);
      drawHubbleRight(center, rotation, posRight);

      Position posLeft;
      posLeft.setPixelsX(1.0);
      posLeft.setPixelsY(8.0);
      drawHubbleLeft(center, rotation, posLeft);
   }*/

   /************************************************
   * BREAK APART
   * Pass parts to the parent function to add all the
   * parts, add them to the simulator, then delete self.
   ****************************************************/
   void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {}) {
      // Add all the parts, add them to the simulator, then delete self
      Satellite::breakApart(sim, { new HubbleComputer(), new HubbleTelescope(), new HubbleLeft(), new HubbleRight() });
   }
};