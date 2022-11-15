#pragma once

#ifndef TWO_D_VALUE
#define TWO_D_VALUE
#include "twoDValue.h"
#endif

/*********************************************
 * Velocity
 * A single velocity of an object in meters / second
 *********************************************/
class Velocity : public TwoDValue
{
public:
   Velocity(double horizontal = 0.0, double vertical = 0.0) : TwoDValue(horizontal, vertical) {};

private:

};