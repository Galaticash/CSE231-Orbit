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
   
   void setRadian(double radians) { this->radAngle = radians; };
   double getRadian() const { return radAngle; }
   
   void setDegree(double degrees);
   double getDegree() const;

   Angle& operator+=(const double rhs);
   Angle& operator-=(const double rhs);
private:
   double radAngle;
   void normalize();
};