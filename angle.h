/***********************************************************************
 * Header File:
 *    Angle : Represents an angle in a 2D space
 * Author:
 *    Eddie McConkie, Logan Huston, Ashley DeMott
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
   Angle(double radAngle = 0.0) : radAngle(radAngle) { this->normalize(); }
  
   // Set an Angle to another Angle
   Angle& operator = (const Angle& twoD) {
      this->radAngle = twoD.radAngle;
      return *this;
   };
   Angle& operator = (const double twoD) {
      this->radAngle = twoD;
      return *this;
   };

   // Addition operators for both Angles and doubles
   Angle& operator +=(const double rhs);
   Angle& operator += (const Angle& twoD);

   // Scale an Angle
   Angle& operator *= (const double scale);

   // Subtraction operators for both Angles and doubles
   Angle& operator -=(const double rhs); 
   Angle& operator -= (const Angle& twoD);

   // If two Angle's radAngle values are the same, same angle
   bool operator == (const Angle& twoD) {
      return this->radAngle == twoD.radAngle;
   }

   // Getters and Setters for Radians
   void setRadian(double radians) { this->radAngle = radians; };
   double getRadian() const { return radAngle; }
   
   // Getters and Setters for Degrees
   void setDegree(double degrees);
   double getDegree() const;

private:
   double radAngle;
   void normalize();
};