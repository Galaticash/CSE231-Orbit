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