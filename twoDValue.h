#pragma once

#include <iostream> 
#include <cmath>

// The default zoom value for the simulator, will use if not set
const double DEFAULT_ZOOM = 128000.0 /* 128km equals 1 pixel */;

/*********************************************
 * 2D Value
 * A pair of values that represent a horizontal and
 * vertical direction. All from Bro. Helfrich's
 * position.h code.
 *********************************************/
class TwoDValue
{
public:
   // If no value given, assumes equals 0
   // Sets Zoom to Default, can be adjusted later with setZoom()
   TwoDValue(double newX = 0.0, double newY = 0.0) { /*this->setZoom(DEFAULT_ZOOM);*/ this->x = newX; this->y = newY; };
   TwoDValue(const TwoDValue& pt) : TwoDValue(pt.x, pt.y) {};

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