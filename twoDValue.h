/***********************************************************************
 * Header File:
 *    Two D Value : A pair of values in an xy/2-Dimensional plane. 
 *    compatible with meters and pixels.
 * Author:
 *    Bro. Helfrich, 
 *    Modified by: Ashley DeMott, Logan Huston
 * Summary:
 *    Stored as meters. Mainly has setters, getters, and adders for meters 
 *    and pixels, with pixel to meter conversion built in. A zoom variable
 *    helps in these calculations for scaling.
 ************************************************************************/
#pragma once
#include <iostream> 
#include <cmath>
#include "angle.h"

class TestTwoDValue;

/*********************************************
 * 2D Value
 * A pair of values that represent a horizontal and
 * vertical direction. All from Bro. Helfrich's
 * position.h code.
 *********************************************/
class TwoDValue
{
public:
   friend TestTwoDValue;

   // If no value given, assumes equals 0
   // Sets Zoom to Default, can be adjusted later with setZoom()
   TwoDValue(double newX = 0.0, double newY = 0.0) { this->x = newX; this->y = newY; };
   TwoDValue(const TwoDValue& pt) : TwoDValue(pt.x, pt.y) {};

   /* OPERATORS */
   TwoDValue& operator = (const TwoDValue& twoD) {
      this->x = twoD.x;
      this->y = twoD.y;
      return *this;
   };

   TwoDValue& operator += (const TwoDValue& twoD) {
      this->x += twoD.x;
      this->y += twoD.y;
      return *this;
   }
   TwoDValue& operator -= (const TwoDValue& twoD) {
      this->x -= twoD.x;
      this->y -= twoD.y;
      return *this;
   }
   TwoDValue& operator *= (const double scale) {
      this->x *= scale;
      this->y *= scale;
      return *this;
   }

   bool operator == (const TwoDValue& twoD) {
      return ((this->x == twoD.x) && (this->y += twoD.y));
   }

   // Getters, for both Meters and Pixels
   double getMetersX()       const { return x; }
   double getMetersY()       const { return y; }
   double getPixelsX()       const { return x / metersFromPixels; }
   double getPixelsY()       const { return y / metersFromPixels; }

   // Setters, for both Meters and Pixels
   void setMeters(double xMeters, double yMeters) { x = xMeters; y = yMeters; }
   void setMetersX(double xMeters) { x = xMeters; }
   void setMetersY(double yMeters) { y = yMeters; }
   void setPixelsX(double xPixels) { x = xPixels * metersFromPixels; }
   void setPixelsY(double yPixels) { y = yPixels * metersFromPixels; }

   // Given an overall change in Meters and an Angle (degrees), adjust x and y values
   void addMeters(double change, Angle angle);

   // Given Meters, adjusts the X or Y value
   void addMetersX(double dxMeters) { setMetersX(getMetersX() + dxMeters); }
   void addMetersY(double dyMeters) { setMetersY(getMetersY() + dyMeters); }
   
   // Given an overall change in Meters and an Angle (degrees), adjust x and y values
   void addPixels(double change, Angle angle);

   // Given Pixels, adjusts the X or Y value
   void addPixelsX(double dxPixels) { setPixelsX(getPixelsX() + dxPixels); }
   void addPixelsY(double dyPixels) { setPixelsY(getPixelsY() + dyPixels); }

   // deal with the ratio of meters to pixels
   void setZoom(double metersFromPixels) { this->metersFromPixels = metersFromPixels; }
   double getZoom() const { return metersFromPixels; }

   // Get the hypotenuse of the x and y values
   double getTotal() {
      // Returns 0 if the x or y value is 0
      if (x == 0 && y == 0)
         return 0;

      // Caclcuates the hypotenuse
      return sqrt(pow(this->x, 2) + pow(this->y, 2));
   }

   // Get the angle between the x and y values
   Angle getAngle();

protected:
   double x;
   double y;
   static double metersFromPixels;
};

// stream I/O useful for debugging
std::ostream& operator << (std::ostream& out, const TwoDValue& twoD);
std::istream& operator >> (std::istream& in, TwoDValue& twoD);

/*********************************************
 * PT
 * Trivial point
 * A simpler version of Position, used in UIDraw
 *********************************************/
struct PT
{
   double x;
   double y;
};