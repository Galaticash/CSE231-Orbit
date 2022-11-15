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
   // constructors
   Acceleration(double horizontal, double vertical) : TwoDValue(horizontal, vertical) {}

private:

};