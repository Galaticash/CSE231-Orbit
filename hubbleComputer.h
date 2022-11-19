#pragma once

#include "part.h"

class HubbleComputer : public Part
{
public:
   HubbleComputer(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {};
/*private:
   createVisual()*/
};