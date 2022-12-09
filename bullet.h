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

 // How far ahead a Bullet is placed in front of the Spaceship (in pixels)
const double ADDED_POSITION = 19.0;

// How much speed is added to a Bullet (in m/s)
const double ADDED_VELOCITY = 9000.0; 

// Lifetime of a Bullet (in frames)
const int BULLET_LIFETIME = 70;

class TestBullet;

/*********************************************
 * Bullet
 * A fragment that is spawned in front of the spaceship.
 *********************************************/
class Bullet : public Fragment
{
public:
   friend TestBullet;  // For testing
   Bullet(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Fragment(pos, vel, angle) {
   
      this->lifetime = BULLET_LIFETIME; // Measured in frames.
      this->radius = 1;
      this->rotationAngle = 0.0;
      
      // Place the Bullet 19 pixels ahead of the Spaceship (given Position)
      //  and add 9000 m/s to the Spaceship's Velocity (given Velcoity)
      this->pos.addPixels(ADDED_POSITION, angle);
      this->vel.addMeters(ADDED_VELOCITY, angle);
   };
};
