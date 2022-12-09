/***********************************************************************
 * Source File:
 *    Fragment : A collisionObject in the orbital simulator that is created
 *    when a satellite or part is destroyed. It has a random lifetime and
 *    will eventually burn up in the atmosphere (expires).
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Contains the logic for break apart, which will just delete itself, 
 *    since fragment doesn't break down.
 ************************************************************************/
#include "fragment.h"
#include "simulator.h"

/*****************************
* UPDATE
* This update checks if the object has expired.
* If they are, set that they need to be destroyed.
* Update normally regardless of expiration.
****************************/
void Fragment::update(double time, double gravity, double radius) {
   // Check if the timer has run out
   if (isExpired())
      this->destroyed = true; // The object is to be destroyed
   else
   {
      this->rotationAngle += FRAGMENT_ROTATION;
      CollisionObject::update(time, gravity, radius); // Update normally
   }
}

/*****************************
* BREAK APART
* Gets rid of the fragment since
* it doesn't break apart.
****************************/
void Fragment::breakApart(Simulator* sim) {
   sim->removeCollider(this); // Remove pointer to self
   delete this; // Delete self
};