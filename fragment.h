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
#include "uiDraw.h"

// The lifetime range of a Fragment (in frames)
const int FRAGMENT_LIFETIME_MIN = 50;
const int FRAGMENT_LIFETIME_MAX = 100;

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
   // Velocity increase is random (5,000-9,000 m/s). <- given in Satellite::breakApart
   // Radius is always 2.
   Fragment(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CollisionObject(pos, vel, angle) 
   { 
      this->lifetime =  random(FRAGMENT_LIFETIME_MIN, FRAGMENT_LIFETIME_MAX); // Give Fragment a random lifetime
      this->radius = 2;
   };

   // Keeps track of the lifetime of the fragment. 
   // Decrements whenever it is called, which should be once per frame.
   bool isExpired() { if (lifetime <= 0) return true; else { lifetime--; return false; } }
   
   void update(double time, double gravity, double radius) {
      // Check if the timer has run out
      if (isExpired())
         this->destroyed = true; // The object is to be destroyed
      else
         CollisionObject::update(time, gravity, radius); // Update normally
   }

   /************************************************************************
    * DRAW FRAGMENT
    * Draw a fragment on the screen.
    *   INPUT  pt     The location of the projectile
    *          age    The age in seconds. The younger, the brighter
    *************************************************************************/
   void draw()
   {
      ColorRect rects[] =
      {
         {-4,1, -4,-1, 4,-1, 4,1, RGB_LIGHT_GREY },
      };

      for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
         glDrawRect(this->pos, Position(), rects[i], this->rotationAngle.getDegree());
   }

   void breakApart(Simulator* sim);

protected:
   int lifetime;
};