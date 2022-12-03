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

/*********************************************
 * Star
 * A star that exists in space. It is part of the background
 * so it has no collision.
 *********************************************/
class Star : public Object
{
public:
   Star(Position pos = Position(), Velocity vel = Velocity(), Angle rotation = Angle()) : Object(pos, vel, rotation) 
   { 
      this->phase = random(0, 200); // TODO: Start at a random phase?
   };

   // TODO: Adjust Phase to not increment infinetley, reset to 0 at some point (work with smaller numbers)
   void update(double time) { this->phase++; };
   int getPhase() { return this->phase; };

private:
   int phase;
};
