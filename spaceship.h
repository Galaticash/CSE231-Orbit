/***********************************************************************
 * Header File:
 *    Spaceship : A satellite in the orbital simulator that the user controls
 *    to clear away space debris.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    The spaceship rotates left and right with the key and thrusts with the
 *    down key. It has a radius of 10 and creates 0 parts and 4 fragments
 *    when destroyed. It starts at (-450px, 450px) with a speed of 
 *    (0.0, -2,000.0). Rotation is by 0.1 Radians and thrusters increase
 *    velocity by 30m/s.
 ************************************************************************/
#pragma once
#include "satellite.h"

const double SHIP_ACCELERATION = 30.0;

/*********************************************
 * Spaceship
 * A type of satellite in the orbit simulator.
 *********************************************/
class Spaceship : public Satellite
{
public:
   Spaceship(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Satellite(pos, vel, angle) {
      this->defective = false;   // The ship will never be defective
      this->thrust = false;      // Ship starts off not moving
      this->radius = 10;         // Radius in pixels;
      this->numFragments = 4;
   };

   void update(double time, double gravity, double planetRadius);

   // Getter and setter for thrust
   void setThrust(bool t) {  this->thrust = t; }
   bool getThrust() { return this->thrust; };

private:
   bool thrust;   // If the Ship's thruster is on (for visuals)
};
