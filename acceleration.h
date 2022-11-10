

#pragma once

#include "twoDValue.h"

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