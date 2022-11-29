#include "simulator.h"

void Simulator::getInput(const Interface* pUI) 
{
   // Check that the Spaceship is still in the Simulation
   if (this->ship != NULL)
   {
      double shipX = 0.0;
      double shipY = 0.0;

      // Get the user's input
      // ERROR: wasd keys aren't working
      if (pUI->isUp())
         shipY += 1.0;
      if (pUI->isDown())
         shipY += -1.0;
      if (pUI->isLeft())
         shipX += -1.0;
      if (pUI->isRight())
         shipX += 1.0;

      // DEBUG: Checking Spaceship movement
      string xDir = "";
      string yDir = "";
      // If the Ship has moved, output direction moved
      if (shipX != 0.0)
         xDir = shipX > 0.0 ? "right " : "left ";
      if (shipY != 0.0)
         yDir = shipY > 0.0 ? "up" : "down";
      cout << xDir << yDir;
      if (!(shipX == 0.0 && shipY == 0.0))
         cout << endl;

      // Add Velocity to the Ship according to the user's input
      moveShip(shipX, shipY);

      // Check for Bullet shooting
      if (pUI->isSpace())
      {
         // Create a new bullet in front of the Spaceship
         createBullet(this->ship->getPosition(), this->ship->getVelocity(), this->ship->getRotation());
      }
   }   

   /*
   if (pUI)
   {
   }
   */

}

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
