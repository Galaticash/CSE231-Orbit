/***********************************************************************
 * Header File:
 *    Earth : A collisionObject in the orbital simulator. It has a gravity 
 *    which pulls other collisionObjects towards it. Cannot be destroyed.
 *    Rotates according to the time dilation of the simulation.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    The earth stays in a fixed position and is never destroyed. All it 
 *    does is rotate and pull things towards it.
 ************************************************************************/
#pragma once
#include "collisionObject.h"

/*********************
* CONSTANTS
*************************/
// Simulator Information
const double FPS = 30.0;                    // The number of frames drawn per second   

// Time on Earth
const double SECONDS_PER_MIN = 60.0;
const double MINUTES_PER_HOUR = 60.0;
const double HOURS_PER_DAY = 24.0;

const double TIME_DILATION = HOURS_PER_DAY * SECONDS_PER_MIN;     // One minute in simulator = One day in real world

// Planet Information
const double SECONDS_DAY = HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MIN; // 24 hours * 60 minutes * 60 seconds
const double ROTATION_SPEED = -(2 * M_PI / FPS) * TIME_DILATION / SECONDS_DAY;

const double GRAVITY = -9.8067;           // Gravity constant in m/s^2
const double EARTH_RADIUS = 6378000.0;    // meters

/*********************************************
 * Earth
 * A planet in the orbital simulator. It has gravity and
 * can be collided with, but can't be destroyed.
 *********************************************/
class Earth : public CollisionObject
{
public:
   Earth(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CollisionObject(pos, vel, angle) {
      this->radius = (EARTH_RADIUS / Position().getZoom());
      this->gravity = GRAVITY;
   };
   
   /********************************
   * UPDATE
   * When the Earth gets updated, it will 
   * not move. Only rotate.
   ***************************************/
   void update(double time, double gravity = 0.0, double radius = 0.0) { 
      Angle test;
      test.addRadian(ROTATION_SPEED);
      this->rotationAngle += test.getRadian();
   }

   bool getDestroyed() { return false; };         // The Earth cannot be destroyed, will always return false
   double getGravity() { return this->gravity; }; // Returns the gravitational constant of Earth

   // The Earth will not break apart
   void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {}) {};

private:
   double gravity;
};
