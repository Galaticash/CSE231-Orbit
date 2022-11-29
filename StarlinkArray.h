#pragma once
#include "part.h"

class StarlinkArray : public Part
{
public:
   StarlinkArray(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {
      //this->radius = 5;
   };
};