#include "simulator.h"

vector<Object*> Simulator::getObjects() {
   // Returns the pointers for all the Objects to be drawn
   vector<Object*> objects;

   // Get pointers for all the Stars
   for (vector<Star>::iterator it = this->stars.begin(); it != this->stars.end(); it++)
   {
      Star addStar = *it;
      objects.push_back(&addStar);
   }
   // Get pointers for all of the Collision Objects
   for (vector<CollisionObject*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
   {
      CollisionObject* addObject = *it;
      objects.push_back(addObject);
   }

   return objects;
}

/* For object in collisionObjs, update their position (according to the amount of time that has passed? Better to leave with Simulator instead of assuming all object will have the correct time*/
void Simulator::update() {

   // Update the phase of the stars (should each start at a random phase)
   /*
   for (vector<Star>::iterator it = this->stars.begin(); it != this->stars.end(); it++)
   {
      
   }*/

   // Update the position of each Object (all other objects are CollisionObjects
   for (vector<CollisionObject*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
   {
      CollisionObject* obj = *it;
      obj->update(TIME);
   }
};