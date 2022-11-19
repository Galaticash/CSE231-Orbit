#pragma once

#ifndef TWO_D_VALUE
#define TWO_D_VALUE
#include "twoDValue.h"
#endif

/*********************************************
 * Acceleration
 * A single acceleration of an object in meters / second^2
 *********************************************/
class Acceleration : public TwoDValue
{
public:
   Acceleration(double horizontal = 0.0, double vertical = 0.0) : TwoDValue(horizontal, vertical) {}

private:

};