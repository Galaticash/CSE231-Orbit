/***********************************************************************
 * Source File:
 *    twoDValue : A type of value with two dimensions.
 * Author:
 *    Br. Helfrich, modified for twoDValue by Ashley DeMott
 * Summary:
 *    Contains the ostream operators for twoDValue.
 ************************************************************************/

#include "twoDValue.h"

/************************************
* GET ANGLE
* Get the angle between the x and y values
 ****************************************/
Angle TwoDValue::getAngle() {
   // Returns 0 if both values are 0
   if (x == 0 && y == 0)
   {
      return Angle(0);
   }

   // Uses same equation as getting Gravity direction
   return Angle(atan2(this->x, this->y));
}

/******************************************
* ADD METERS
* Given an overall change in Meters and an 
* Angle (degrees), adjust x and y values.
**********************************************/
void TwoDValue::addMeters(double totalMeters, Angle angle) {
   double xMeters = totalMeters * sin(angle.getRadian());
   double yMeters = totalMeters * cos(angle.getRadian());

   this->addMetersX(xMeters);
   this->addMetersY(yMeters);
};

/**********************************
* ADD PIXELS
* Given an overall change in Meters and an 
* Angle (degrees), adjust x and y values
********************************************/
void TwoDValue::addPixels(double totalPixels, Angle angle) {
   double xPixels = totalPixels * sin(angle.getRadian());
   double yPixels = totalPixels * cos(angle.getRadian());

   this->addPixelsX(xPixels);
   this->addPixelsY(yPixels);
}

/******************************************
 * POSITION insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream& operator << (std::ostream& out, const TwoDValue& twoD)
{
   out << "(" << twoD.getMetersX() << "m , " << twoD.getMetersY() << "m)";
   return out;
}
   
/*******************************************
* POSITION extraction
*       Prompt for coordinates
******************************************/
std::istream& operator >> (std::istream& in, TwoDValue& twoD)
{
   double x;
   double y;
   in >> x >> y;

   twoD.setMetersX(x);
   twoD.setMetersY(y);

   return in;
}
