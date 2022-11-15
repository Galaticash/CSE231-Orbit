#pragma once
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