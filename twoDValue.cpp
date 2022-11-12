/***********************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "twoDValue.h"

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
