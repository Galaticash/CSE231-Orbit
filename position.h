/***********************************************************************
 * Header File:
 *    Position : The representation of a 2D location in space
 * Author:
 *    Ashley DeMott
 * Summary:
 *    Everything we need to know about a location on the screen
 *    or the location on the field.
 ************************************************************************/
#pragma once
#ifndef TWO_D_VALUE
#define TWO_D_VALUE
#include "twoDValue.h"
#endif

class TestPosition;

/*********************************************
 * Position
 * A single position on the field in Meters/Pixels
 *********************************************/
class Position : public TwoDValue
{
public:
   friend TestPosition; // For test cases

   // Constructors given x, y doubles or another Position
   Position(double x = 0.0, double y = 0.0) : TwoDValue(x, y) {};
   Position(const Position& pt) : TwoDValue(pt.x, pt.y) {};

   // Calculates the number of pixels between two Positions
   double pixelsBetween(const Position& other) {
      return sqrt(pow((this->getPixelsX() - other.getPixelsX()), 2) + pow((this->getPixelsY() - other.getPixelsY()), 2));
   }

   // Calculates the number of meters between two Positions
   double distanceBetween(const Position& other) {
      return sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2));
   }
};