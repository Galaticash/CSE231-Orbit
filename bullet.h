/***********************************************************************
 * Header File:
 *    Bullet : A fragment in the orbital simulator that is fired from the
 *    spaceship.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    A bullet has a fixed lifetime and a fixed speed increase from creation.
 ************************************************************************/
#pragma once
#include "fragment.h"

const double ADDED_POSITION = 19.0;
const double ADDED_VELOCITY = 9000.0;

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

      // TODO: Move the pythagorean theorem out of object and into 2DPosition and rename.
      // Add 9000.0 m/s to velocity from ship. Position is 19 pixels in front of the ship.
      double dx = this->horizontalAcceleration(ADDED_VELOCITY, angle.getDegree());
      double dy = this->verticalAcceleration(ADDED_VELOCITY, angle.getDegree());
      double x = this->horizontalAcceleration(ADDED_POSITION, angle.getDegree());
      double y = this->verticalAcceleration(ADDED_POSITION, angle.getDegree());
      
      this->pos.addPixelsX(x);
      this->pos.addPixelsY(y);
      this->vel.addMetersX(dx);
      this->vel.addMetersY(dy); 
   };
};
