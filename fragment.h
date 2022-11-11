

#pragma once

#include "collisionObject.h"

/*********************************************
 * Fragment
 * A piece from a destroyed satellite or a destroyed part.
 * Small enough to eventually burn up and be deleted from 
 * the simulation.
 *********************************************/
class Fragment : public CollisionObject
{
public:
   Fragment();
   Fragment(TwoDValue pos, TwoDValue vel, Angle angle);

   bool isExpired() { return true; }

private:
   int lifetime;
};