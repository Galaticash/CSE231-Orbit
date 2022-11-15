/***********************************************************************
 * Header File:
 *    Angle : Represents an angle in a 2D space
 * Author:
 *    Eddie McConkie, Logan Huston
 * Summary:
 * Calculates angle with radians and can accept both radians and degrees
 ************************************************************************/
#pragma once

 /***********************************
 * ANGLE
 * The angle class
 *************************************/
class Angle
{
public:
   Angle() : radAngle(0.0) {}
   Angle(double radAngle) : radAngle(radAngle) {}
   double getRadAngle() const { return radAngle; }
   double getDegAngle() const;
   Angle& operator+=(const double rhs);
   Angle& operator-=(const double rhs);
private:
   double radAngle;
   void normalize();
};