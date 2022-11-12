#pragma once
/*********************************************
 * Star
 * A star that exists in space. It is part of the background 
 * so it has no collision.
 *********************************************/
#include "object.h"

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
