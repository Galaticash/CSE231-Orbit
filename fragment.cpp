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
* BREAK APART
* Gets rid of the fragment since 
* it doesn't break apart.
****************************/
void Fragment::breakApart(Simulator* sim) {
   sim->removeCollider(this); // Remove pointer to self
   delete this; // Delete self
};