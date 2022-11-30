#pragma once
#include "object.h"

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
      this->phase = 0; // TODO: Start at a random phase?
   };

   // TODO: Adjust Phase to not increment infinetley, reset to 0 at some point (work with smaller numbers)
   void update(double time) { this->phase++; };
   int getPhase() { return this->phase; };

private:
   int phase;
};
