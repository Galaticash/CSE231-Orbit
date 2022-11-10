

#pragma once

/*********************************************
 * 2D Value
 * A pair of values that represent a horizontal and
 * vertical direction. Dealing with zoom from Bro. Helfrich's
 * position.h code.
 *********************************************/
class TwoDValue
{
public:
   // Constructors
   TwoDValue() : horizontal(0.0), vertical(0.0) {}
   TwoDValue(double horizontal, double vertical);

   // Getters
   double getMetersHorizontal()  const { return horizontal; }
   double getMetersVertical()    const { return vertical; }
   double getPixelsHorizontal()  const { return horizontal / metersFromPixels; }
   double getPixelsVertical()    const { return vertical / metersFromPixels; }
   
   // Setters
   void setMeters(double hMeters, double vMeters) { horizontal = hMeters; vertical = vMeters; }
   void setMetersHorizontal(double hMeters)  { horizontal = hMeters; }
   void setMetersVertical(double vMeters)    { vertical = vMeters; }
   void setPixelsHorizontal(double hPixels)  { horizontal = hPixels * metersFromPixels; }
   void setPixelsVertical(double vPixels)    { vertical = vPixels * metersFromPixels; }
   void addMetersHorizontal(double dhMeters) { setMetersHorizontal(getMetersHorizontal() + dhMeters); }
   void addMetersVertical(double dvMeters)   { setMetersVertical(getMetersVertical() + dvMeters); }
   void addPixelsHorizontal(double dhPixels) { setPixelsHorizontal(getPixelsHorizontal() + dhPixels); }
   void addPixelsVertical(double dvPixels)   { setPixelsVertical(getPixelsVertical() + dvPixels); }

   // deal with the ratio of meters to pixels
   void setZoom(double metersFromPixels)     { this->metersFromPixels = metersFromPixels; }
   double getZoom()              const { return metersFromPixels; }

private:
   double horizontal;
   double vertical;
   static double metersFromPixels;
};