#include "simulator.h"

void Simulator::moveShip(double x, double y) {};

/* For object in collisionObjs, update their position 
   (according to the amount of time that has passed? 
   Better to leave with Simulator instead of assuming 
   all Objects will have the correct time */

// ERROR: Wierd, throwing a linking error when defined here
/*
void Simulator::update() {

   // Update the phase of the stars (should each start at a random phase)
   /*
   for (vector<Star>::iterator it = this->stars.begin(); it != this->stars.end(); it++)
   {
      
   }
}*/


vector<Object*> Simulator::getObjects() {
   // Returns the pointers for all the Objects to be drawn
   vector<Object*> objects;

   // Get pointers for all the Stars
   for (vector<Star>::iterator it = this->stars.begin(); it != this->stars.end(); it++)
   {
      // Add a pointer to the Star (cast to Object*)
      objects.push_back(&(*it));
   }
   // Get pointers for all of the Collision Objects
   for (vector<CollisionObject*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
   {
      // Add the Collision Object pointer (cast to Object*)
      objects.push_back(*it);
   }

   return objects;
}
