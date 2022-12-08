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

   void update(double time, double gravity, double planetRadius) {
      // If the ship's thruster is on (from user input)
      if(thrust)
      {
         // TODO: Acceleration math (**see instructions)
         // 3600 (sim) to 1 seconds (real), 30FPS

         /* INSTRUCTIONS
          Pressing the down-arrow will accelerate the spaceplane by 30.0 m/s2.

          Acceleration will be along the direction the Dream Chaser is pointed,
          not the direction of travel.
          
          To determine how much the acceleration will affect the velocity of the ship,
          it is necessary to take into account the direction the ship is pointed and
          how many seconds the thrust counts in the simulation.

          For example, if the simulation has 3600 seconds of simulation
          time to 1 second of player time, and if the simulation is running
          at 30 frames/second, then one depression of the button will accelerate
          the ship for 120 seconds (or 2 minutes).

          Thus vt = v0 + a t so the change in speed will be 600 m/s.

          - - -
          Add Meters is the a * t part of the equation, and a = 30m/s2, so t is the key part
         */
         
         // Accelerate 30.0 m/s^2 in facing direction
         // TODO: Add a multiplier?
         // TODO: Add per button press or per update?
         this->vel.addMeters(SHIP_ACCELERATION, rotationAngle);

         // ERROR: Adds velocity in a constant direction, doesn't take current facing into account
         // Increase velocity by 30 m/s^2. Calculate x and y velocity from total.
         //double ddx = this->horizontalAcceleration(30.0, rotationAngle.getDegree());
         //double ddy = this->verticalAcceleration(30.0, rotationAngle.getDegree());

         //this->vel.addMetersX(ddx);
         //this->vel.addMetersY(ddy);
      }

      // Then update normally
      CollisionObject::update(time, gravity, planetRadius);
   }

   // Getter and setter for thrust
   void setThrust(bool t) {  this->thrust = t; }
   bool getThrust() { return this->thrust; };

private:
   bool thrust;   // If the Ship's thruster is on (for visuals)
};
