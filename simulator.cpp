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

/********************************************
* UPDATE
* Updates all items in the simulator, according to the amount of
* time that has passed and the affect of the Earth's gravity
*******************************************************/
void Simulator::update()
{
   // Collect all objects that are marked for destruction
   vector<CollisionObject*> destroyObjs = {};

   // Check for collisions between the Simulator's collisionObjects,
   //  will update the destroyed bool for any that collide
   updateCollisions();

   // For every Collision Object in the Simulator,
   for (vector<CollisionObject*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
   {
      // If it has been marked for destruction,
      //  (either from a collision or a timer expiring)
      if ((*it)->getDestroyed())
         // Add to list of objects to break apart
         destroyObjs.push_back(*it);

      // Otherwise, has not been destroyed, update Position
      //  (NOTE: Converts the Earth's radius from Pixels to Meters using zoom)
      else
         (*it)->update(this->timeDialation, this->planet->getGravity(), (this->planet->getRadius() * Position().getZoom()));
   }

   // For every Collision Object that has been marked for destruction,
   for (vector<CollisionObject*>::iterator it = destroyObjs.begin(); it != destroyObjs.end(); it++)
      // Break the object apart, adding their subParts to the Simulator's list of collisionObjects
      ((CollisionObject*)(*it))->breakApart(this);

   destroyObjs.clear(); // Clear the vector of Collision Objects

   // Updates the frame of all the Stars
   for (vector<Star>::iterator it = this->stars.begin(); it != this->stars.end(); it++)
      (*it).update(this->timeDialation);
}

/******************************
* GET OBJECTS
* Creates a list of all objects in the simulator.
**************************************/
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

/*************************************
* UPDATE COLLISIONS
* Updates the collision of all objects in the sim by
* looping through the list of objects twice, with 
* the inner loop having one less than the outer loop.
*******************************************/
void Simulator::updateCollisions() {
   // DEGBUG: Efficiency of this algorithm
   //int outerCount = 0; // 12 <-- 12 Objects total
   //int innerCount = 0; // 66 <-- comparisons (12 + 11 + 10 + 9..)

   // For every Collison Object in the Simulator's collisionObjects,
   for (vector<CollisionObject*>::iterator objOneIt = this->collisionObjects.begin(); objOneIt != this->collisionObjects.end(); objOneIt++) 
   {
      // For every Collison Object in the Simulator's collisionObjects,
      for (vector<CollisionObject*>::iterator objOneIt = this->collisionObjects.begin(); objOneIt != this->collisionObjects.end(); objOneIt++)
      {
         // Check against every object except itself
         for (vector<CollisionObject*>::iterator objTwoIt = objOneIt + 1; objTwoIt != this->collisionObjects.end(); objTwoIt++)
         {
            // Check if the two Objects have hit eachother,
            if ((*objOneIt)->isHit(*(*objTwoIt)))
            {
               // Tell the second object it was also hit
               (*objTwoIt)->setDestroyed(true);
            }
         }
      }
   };
};