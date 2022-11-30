/***********************************************************************
 * Header File:
 *    Fragment : A collisionObject in the orbital simulator that is created
 *    when a satellite or part is destroyed. It has a random lifetime and 
 *    will eventually burn up in the atmosphere (expires).
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Fragment keeps a counter of how long it has been alive. When it's 
 *    lifetime runs out, it sets itself up to be destroyed. When created
 *    it is given a random lifetime and velocity.
 ************************************************************************/
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
   // Lifetime is random (50-100 frames). 
   // Velocity increase is random (5,000-9,000 m/s).
   // Radius is always 2.
   Fragment(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CollisionObject(pos, vel, angle) { this->lifetime = 50; this->radius = 2; };

   // Keeps track of the lifetime of the fragment. 
   // Decrements whenever it is called, which should be once per game cycle.
   bool isExpired() { if (lifetime <= 0) return true; else { lifetime--; return false; } }
   
   void update(double time = 0.0, double gravity = 0.0, double radius = 0.0) {
      if (isExpired())
      {
         this->destroyed = true; // The object is to be destroyed
      }
      else
         CollisionObject::update(time, gravity, radius);
   }
   void breakApart(Simulator* sim);

protected:
   int lifetime;
};