/***********************************************************************
 * Source File:
 *    GPS : A satellite in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    GPS has a radius of 12 and creates 3 parts and 2 fragments when destroyed.
 *    These remain in Geosynchronous orbit at a constant velocity. When
 *    directly above the earth (0.0, 26,560,000.0), the velocity is (-3,880.0, 0.0).
 ************************************************************************/
#pragma once
#include "gps.h"

/*********************************
* UPDATE
* The GPS satelite will always point to the earth,
* so it's rotation must match that of the earth.
*********************************************/
void GPS::update(double time, double gravity, double planetRadius)
{
   // Don't update rotation if the satellite has become defective.
   if (!defective)
   {
      // GPS will rotate to face the Earth (direction of gravity)
      this->rotationAngle.setRadian(gravityDirection(pos.getMetersX(), pos.getMetersY()));
      this->rotationAngle.addDegree(GPS_ROTATION_OFFSET);
   }
   Satellite::update(time, gravity, planetRadius);
}