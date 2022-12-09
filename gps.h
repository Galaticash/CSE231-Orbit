/***********************************************************************
 * Header File:
 *    GPS : A satellite in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    GPS has a radius of 12 and creates 3 parts and 2 fragments when destroyed.
 *    These remain in Geosynchronous orbit at a constant velocity. When 
 *    directly above the earth (0.0, 26,560,000.0), the velocity is (-3,880.0, 0.0).
 ************************************************************************/
#pragma once
#include "satellite.h"

// GPS parts
#include "gpsCenter.h"
#include "gpsLeft.h"
#include "gpsRight.h"

// The 'facing' direction of GPS drawing is off by 90 degrees
const double GPS_ROTATION_OFFSET = 90;

/*********************************************
 * GPS
 * A type of satellite in the orbit simulator.
 *********************************************/
class GPS : public Satellite
{
public:
   GPS(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Satellite(pos, vel, angle)
   {
      this->radius = 12; // Radius in pixels;
      this->numFragments = 2;
   };

   /************************************************
   * BREAK APART
   * Pass parts to the parent function to add all the 
   * parts, add them to the simulator, then delete self.
   ****************************************************/
   void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {}) {
      // Add all the GPS parts, add them to the simulator, then delete self
      Satellite::breakApart(sim, { new GPSCenter(), new GPSLeft(), new GPSRight() });
   }

   /*********************************
   * UPDATE
   * The GPS satelite will always point to the earth,
   * so it's rotation must match that of the earth.
   *********************************************/
   void update(double time, double gravity, double planetRadius);
};
