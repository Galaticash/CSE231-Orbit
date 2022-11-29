#pragma once
#include "part.h"

class HubbleLeft : public Part
{
public:
   HubbleLeft(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {};
};