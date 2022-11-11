

#pragma once

#include "fragment.h"

/*********************************************
 * Bullet
 * A fragment that is spawned in front of the spaceship.
 *********************************************/
class Bullet : public Fragment
{
public:
   Bullet();
   Bullet(TwoDValue pos, TwoDValue vel, Angle angle);
   
private:

};
