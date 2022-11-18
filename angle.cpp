/***********************************************************************
 * Source File:
 *    Angle : Represents an angle in a 2D space
 * Author:
 *    Eddie McConkie, Logan Huston
 * Summary:
 * Calculates angle with radians and can accept both radians and degrees
 ************************************************************************/

#define _USE_MATH_DEFINES
#include <cmath>
#include "angle.h"

/***********************************
* NORMALIZE
* When an angle is 2*PI or 360 degrees, subtract one of those two max values
* as many times as needed to be under the max.
*************************************/
void Angle::normalize()
{
   // cycleOffset is the number of full cycles the angle will need to be
   // turned back to fit within the range
   int cycleOffset = floor(radAngle / (2.0 * M_PI));
   radAngle -= cycleOffset * (2.0 * M_PI);
}

void Angle::setDegree(double degree) { this->radAngle = degree * M_PI / 180.0; }
double Angle::getDegree() const { return radAngle * 180.0 / M_PI; }

Angle& Angle::operator+=(const double rhs)
{
   radAngle += rhs;
   normalize();
   return *this;
}

Angle& Angle::operator-=(const double rhs)
{
   radAngle -= rhs;
   normalize();
   return *this;
}