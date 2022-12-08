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
// Math Information
const double PI = 3.1415926;            // The value of Pi

// TODO: I'm sure there's a better way to calculate framerate
//  (maybe using gl's framerate or something), but this will do for now
// Simulator Information
const double FPS = 30;                    // The number of frames drawn per second     
const double TIME_DILATION = 24 * 60;     // One minute in simulator = One day in real world

// Planet Information
const double SECONDS_DAY = 24 * 60 * 60; // 24 hours * 60 minutes * 60 seconds
const double ROTATION_SPEED = -(2 * PI / FPS) * TIME_DILATION / SECONDS_DAY;

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
   
   void update(double time, double gravity = 0.0, double radius = 0.0) { 
      // The Earth will not move, only rotate
      Angle test;
      test.setDegree(ROTATION_SPEED);
      this->rotationAngle += test.getRadian();
   }

   bool getDestroyed() { return false; };         // The Earth cannot be destroyed, will always return false
   double getGravity() { return this->gravity; }; // Returns the gravitational constant of Earth

   // The Earth will not break apart
   void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {}) {};

private:
   double gravity;
};
