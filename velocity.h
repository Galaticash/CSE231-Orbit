

#pragma once

#include "twoDValue.h"

/*********************************************
 * Velocity
 * A single velocity of an object in meters / second
 *********************************************/
class Velocity : public TwoDValue
{
public:
   // constructors
   Velocity(double horizontal, double vertical) : TwoDValue(horizontal, vertical) {}

private:

};