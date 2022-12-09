/***********************************************************************
 * Source File:
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
#include "spaceship.h"

/*********************************
* UPDATE
* If the thrusters are on, move 30 m/s^2.
* Otherwise, update normally.
*************************************/
void Spaceship::update(double time, double gravity, double planetRadius) {
   // If the ship's thruster is on (from user input)
   if (thrust)
   {
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

      // TODO: Add a multiplier?
      // TODO: Add per button press or per update?
      // Accelerate 30.0 m/s^2 in facing direction
      this->vel.addMeters(SHIP_ACCELERATION, rotationAngle);
   }

   // Then update normally
   CollisionObject::update(time, gravity, planetRadius);
}