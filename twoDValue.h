#pragma once

/*********************************************
 * 2D Value
 * A pair of values that represent a horizontal and
 * vertical direction. All from Bro. Helfrich's
 * position.h code.
 *********************************************/

#include <iostream> 
#include <cmath>

class TwoDValue
{
public:
   // Constructor
   // If no value given, assumes equals 0
   TwoDValue(double newX = 0, double newY = 0) { this->x = newX; this->y = newY; };

   TwoDValue& operator = (const TwoDValue& twoD) {
      x = twoD.x;
      y = twoD.y;
      return *this;
   };

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
   
   // Asjust meters/pixel value
   void addMetersX(double dxMeters) { setMetersX(getMetersX() + dxMeters); }
   void addMetersY(double dyMeters) { setMetersY(getMetersY() + dyMeters); }
   void addPixelsX(double dxPixels) { setPixelsX(getPixelsX() + dxPixels); }
   void addPixelsY(double dyPixels) { setPixelsY(getPixelsY() + dyPixels); }

   // deal with the ratio of meters to pixels
   void setZoom(double metersFromPixels) { this->metersFromPixels = metersFromPixels; }
   double getZoom() const { return metersFromPixels; }

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
 *********************************************/
// TODO: Remove? smaller version of Position class
struct PT
{
   double x;
   double y;
};