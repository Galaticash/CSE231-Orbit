/***********************************************************************
 * Header File:
 *    Star : An object in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    A star remains in the background and cannot be collided with. Has 
 *    phases that emulate twinkling.
 ************************************************************************/
#pragma once
#include "object.h"
#include "uiDraw.h"

const int STAR_PHASE_LIMIT = 250; // The max star phase

/*********************************************
 * Star
 * A star that exists in space. It is part of the background
 * so it has no collision and is not affected by Earth's gravity.
 *********************************************/
class Star : public Object
{
public:
   Star(Position pos = Position(), Velocity vel = Velocity(), Angle rotation = Angle()) : Object(pos, vel, rotation)
   {
      this->phase = random(0, STAR_PHASE_LIMIT); /* Start at a random phase */
   };

   /******************************************
   * UPDATE
   * Stars don't need their position or velocity updated,
   * so only their phase is updated
   ********************************************/
   void update(double time) {
      if (phase > STAR_PHASE_LIMIT)
         this->phase = 0; // Resets phase to 0, as to not increment infinitely
      else
         this->phase++; // Increment phase
   };

   /******************************************
   * GET PHASE
   * Returns the Star's current phase
   ********************************************/
   int getPhase() { return this->phase; };

private:
   int phase;  // The current phase of the Star, used to draw a Star differently
};
