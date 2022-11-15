#pragma once

#include "fragment.h"

class BulletTest;

/*********************************************
 * Bullet
 * A fragment that is spawned in front of the spaceship.
 *********************************************/
class Bullet : public Fragment
{
public:
   friend BulletTest;
   Bullet() : Bullet(Position(), Velocity(), Angle()) {};
   Bullet(Position pos, Velocity vel, Angle angle) : Fragment(pos, vel, 0.0) {};
};
