#pragma once

#include "fragment.h"

/*
#ifndef BULLET_VALUES
#define BULLET_VALUES
   double ADDED_POSITION_PX = 19.0;
   double ADDED_VELOCITY_M = 9000.0;
#endif
*/

class TestBullet;

/*********************************************
 * Bullet
 * A fragment that is spawned in front of the spaceship.
 *********************************************/
class Bullet : public Fragment
{
public:
   friend TestBullet;
   Bullet(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Fragment(pos, vel, angle) {
   
      this->lifetime = 70; // Measured in frames.
      this->radius = 1;
      // Add 9000.0 m/s to velocity from ship. Position is 19 pixels in front of the ship.
      
      /*
      const double ADDED_POSITION_PX = 19.0;
      const double ADDED_VELOCITY_M = 9000.0;

      TODO: Pyth theorem
      this->pos.addPixels(ADDED_POSITION_PX);
      this->pos.addPixelsX(ADDED_POSITION_PX);
      this->pos.addPixelsY(ADDED_POSITION_PX);
      
      TODO: Pyth theorem
      this->vel.addMeters(ADDED_VELOCITY_M);
      this->vel.addMetersX(ADDED_VELOCITY_M);
      this->vel.addMetersY(ADDED_VELOCITY_M);
      */

      // TODO: Move the pythagorean theorem out of object and into 2DPosition and rename.
      double dx = this->horizontalAcceleration(9000.0, angle.getDegree());
      double dy = this->verticalAcceleration(9000.0, angle.getDegree());
      double x = this->horizontalAcceleration(19.0, angle.getDegree());
      double y = this->verticalAcceleration(19.0, angle.getDegree());

      this->pos.addPixelsX(x);
      this->pos.addPixelsY(y);
      this->vel.addMetersX(dx);
      this->vel.addMetersY(dy);

      
   };
};
