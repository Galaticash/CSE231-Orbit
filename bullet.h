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
   
      // TODO: Pyth theorem
      //this->pos.addPixels(ADDED_POSITION_PX);
      //this->pos.addPixelsX(ADDED_POSITION_PX);
      //this->pos.addPixelsY(ADDED_POSITION_PX);

      // TODO: Pyth theorem
      //this->vel.addMeters(ADDED_VELOCITY_M);
      //this->vel.addMetersX(ADDED_VELOCITY_M);
      //this->vel.addMetersY(ADDED_VELOCITY_M);
   };
};
