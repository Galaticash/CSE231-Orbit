/***********************************************************************
 * Source File:
 *    Simulator : Runs the main interactions in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Methods for getting input from the user and getting all Objects.
 ************************************************************************/
#include "simulator.h"

// How many m/s^2 the ship accelerates with one press of the down arrow
// Instructions say 30.0 m/s, but too fast with current implementation
const double SHIP_ACCELERATION = 5.0; 

void Simulator::getInput(const Interface* pUI)
{
   // NOTE: Sim meant to work with only left, right, and down arrow keys.
   // ERROR: J key shoots bullets, e unlocks thrusters??????
   // D key makes ship spin uncontrollably

   // Check that the Spaceship is still in the Simulation
   if (this->ship != NULL)
   {
      Velocity addedVelocity = Velocity();  // The Velocity to be added
      Angle shipRotation = 0.0;  // The change in rotation

      // Get the user's input
      // Ship turning
      // TODO: Normalize not working properly?
      if (pUI->isLeft())
         shipRotation.setDegree(-0.1);
      if (pUI->isRight())
         shipRotation.setDegree(0.1);
      ship->addRotation(shipRotation);

      // TODO: Acceleration math
      // 3600 (sim) to 1 seconds (real), 30FPS

      // Set if the ship's thruster is on
      if (pUI->isDown()) {
         // Accelerate 30.0 m/s^2 in facing direction
         addedVelocity.addMeters(SHIP_ACCELERATION * TIME, ship->getRotation());
         ship->setThrust(true);
      }
      else
         ship->setThrust(false);

      // Add Velocity to the Ship according to the user's input
      // NewVel = InitialVel + acceleration * time
      // AddedVel = acceleration * TIME
      ship->addVelocity(addedVelocity);

      // Check for Bullet shooting
      if (pUI->isSpace())
      {
         // Create a new bullet in front of the Spaceship
         createBullet(this->ship->getPosition(), this->ship->getVelocity(), this->ship->getRotation());
      }
   }

   /* TESTING: toggle debug view <-- would have to add more key checks to Interface
   * // Would also have to move debug bool to Simulator
   if (pUI)
   {
      this->debug = true;
      this->debug = debug ? false : true;
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
