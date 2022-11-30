#pragma once

#include "part.h"

class StarlinkBody : public Part
{
public:
   StarlinkBody(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {
      this->radius = 2; // Radius in pixels
      this->numFragments = 3;
   };
};