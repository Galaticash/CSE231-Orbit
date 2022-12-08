/***********************************************************************
 * Source File:
 *    Simulator : Runs the main interactions in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Methods for getting input from the user and getting all Objects.
 ************************************************************************/
#include "simulator.h"

/*********************************************
 * GET INPUT
 * Handles key input from the user, given the Interface
 *********************************************/
void Simulator::getInput(const Interface* pUI)
{
   // NOTE: Sim meant to work with only left, right, and down arrow keys.
   // ERROR: J key shoots bullets, e unlocks thrusters??????
   // D key makes ship spin uncontrollably

   // Check that the Spaceship is still in the Simulation
   if (this->ship != NULL)
   {
      Angle shipRotation = 0.0;  // The change in rotation

      // Ship turning (left and right arrows)
      // TODO: Normalize not working properly? <-- That's why the ship is resetting to 0
      if (pUI->isLeft())
         shipRotation.setDegree(-0.1);
      if (pUI->isRight())
         shipRotation.setDegree(0.1);
      ship->addRotation(shipRotation);

      // Set if the ship's thruster is on (down arrow)
      if (pUI->isDown())
      {/* TODO: Add per button press or per update?
         Velocity v;
         v.addMeters(SHIP_ACCELERATION * 120, ship->getRotation());
         ship->addVelocity(v);        */
         ship->setThrust(true);
      }
      else
         ship->setThrust(false);

      // Check for Bullet shooting (spacebar)
      if (pUI->isSpace())
      {
         // Create a new bullet in front of the Spaceship
         createBullet(this->ship->getPosition(), this->ship->getVelocity(), this->ship->getRotation());
      }
   }

   // EXTRA: Toggle debug view (up arrow)
   if (pUI->isUp())
      this->debug = debug ? false : true;
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
