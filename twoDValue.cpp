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
   if (x == 0 && y == 0)
   {
      return Angle(0);
   }

   // Sin A = opposite / hyp
   double sine = this->y / getTotal();
   return Angle(asin(sine));
}

/******************************************
* ADD METERS
* Given an overall change in Meters and an 
* Angle (Degrees), adjust x and y values.
**********************************************/
void TwoDValue::addMeters(const double totalMeters, const Angle angle) {
   // NOTE: Used in Spaceship, Bullet, Explosions
   // 'Working' version
   /*
   double xMeters = totalMeters * sin(angle.getDegree()); // TODO: Radians in other equation, degrees here??
   double yMeters = totalMeters * cos(angle.getDegree());
   */
   
   // 'Correct' version 
   // ERROR: Ship.. doesn't move in facing direction???
   /**/
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
void TwoDValue::addPixels(double change, Angle angle) {
   // NOTE: Used in Bullet and Explosion
   // 'Working' version
   /*
   double yVal = change * cos(angle.getDegree());
   double xVal = change * sin(angle.getDegree());
   */

   // Wait... Pixels is set up the same HEH?
   // And when I 'fix' this, it messes up rotation??? HOW???
   // Display is correct, but debug shows incorrect???
   // 'Correct' version
   /**/
   double yVal = change * cos(angle.getRadian());
   double xVal = change * sin(angle.getRadian());

   this->addPixelsX(xVal);
   this->addPixelsY(yVal);
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
