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

 /*********************************************
  * Star
  * A star that exists in space. It is part of the background
  * so it has no collision.
  *********************************************/
class Star : public Object
{
public:
   Star() : Star(Position()) {};
   Star(Position pos) : Object(Position()) { this->phase = 0; };

   void update(double time) { this->phase++; };
   int getPhase() { return this->phase; };

private:
   int phase;
};
