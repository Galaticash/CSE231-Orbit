#pragma once

#include "part.h"

//string drawType = "hubbleTelescope";

class HubbleTelescope : public Part
{
public:
   HubbleTelescope(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {};
};