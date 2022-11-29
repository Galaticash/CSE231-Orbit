/***********************************************************************
 * Source File:
 *    twoDValue : A type of value with two dimensions
 * Author:
 *    Br. Helfrich, modified for twoDValue by Ashley DeMott
 * Summary:
 *    ostream operators for twoDValue
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
