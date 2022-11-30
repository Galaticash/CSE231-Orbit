/***********************************************************************
 * Header File:
 *    Point : The representation of a position 
 * Author:
 *    Br. Helfrich
 *    Modified by Ashley DeMott
 * Summary:
 *    Everything we need to know about a location on the screen
 *    or the location on the field.
 ************************************************************************/
#pragma once
#ifndef TWO_D_VALUE
#define TWO_D_VALUE
#include "twoDValue.h"
#endif

/* Should not know anything about vel, etc? Unless using the methods?
class TestPosition;
class Acceleration;
class Velocity;
*/

class TestPosition;

/*********************************************
 * Position
 * A single position on the field in Meters/Pixels
 *********************************************/
class Position : public TwoDValue
{
public:
   friend TestPosition;
   Position(double x = 0.0, double y = 0.0) : TwoDValue(x, y) {};
   Position(const Position& pt) : TwoDValue(pt.x, pt.y) {};

   // Gets the number of pixels between two Positions (as a double/float)
   double pixelsBetween(const Position& other)
   {
      return sqrt(pow((this->getPixelsX() - other.getPixelsX()), 2) + pow((this->getPixelsY() - other.getPixelsY()), 2));
   }

   // Gets the number of meters between two Positions
   double distanceBetween(const Position& other) {
      return sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2));
   }
};

/*********************************************
 * COMPUTE DISTANCE
 * Find the distance between two positions
 *********************************************/
/*
inline double computeDistance(const Position& pos1, const Position& pos2)
{
   return sqrt((pos1.getMetersX() - pos2.getMetersX()) * (pos1.getMetersX() - pos2.getMetersX()) +
               (pos1.getMetersY() - pos2.getMetersY()) * (pos1.getMetersY() - pos2.getMetersY()));
}
*/