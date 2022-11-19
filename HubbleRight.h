#pragma once

#include "part.h"

class HubbleRight : public Part
{
public:
   HubbleRight(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {};
   /*private:
      createVisual()*/
};