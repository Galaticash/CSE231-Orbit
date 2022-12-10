/***********************************************************************
 * Source File:
 *    Simulator : Runs the main interactions in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Methods for getting input from the user and getting all Objects.
 ************************************************************************/
#include "simulator.h"

/*************************************
* ADD OBJECTS
* Adds Objects to the simulator
***************************************/
void Simulator::addObjects()
{
   // Create and add the user-controlled Spaceship
   Position shipInitial = Position(); // Position given in pixels
   shipInitial.setPixelsX(-450);
   shipInitial.setPixelsY(450);
   this->ship = new Spaceship(shipInitial, Velocity(0.0, -2000.0));
   addCollider(ship);

   // Create and add the Earth at the center of the Simulation
   this->planet = new Earth();
   addCollider(planet);

   // Sputnik
   addCollider(new Sputnik(Position(-36515095.13, 21082000.0), Velocity(2050.0, 2684.68)));

   // GPS
   addCollider(new GPS(Position(0.0, 26560000.0), Velocity(-3880.0, 0.0)));
   addCollider(new GPS(Position(23001634.72, 13280000.0), Velocity(-1940.00, 3360.18)));
   addCollider(new GPS(Position(23001634.72, -13280000.0), Velocity(1940.00, 3360.18)));
   addCollider(new GPS(Position(0.0, -26560000.0), Velocity(3880.0, 0.0)));
   addCollider(new GPS(Position(-23001634.72, -13280000.0), Velocity(1940.00, -3360.18)));
   addCollider(new GPS(Position(-23001634.72, 13280000.0), Velocity(-1940.00, -3360.18)));

   // Hubble
   addCollider(new Hubble(Position(0.0, -42164000.0), Velocity(3100.0, 0.0)));

   // Dragon
   addCollider(new Dragon(Position(0.0, 8000000.0), Velocity(-7900.0, 0.0)));

   // StarLink
   addCollider(new Starlink(Position(0.0, -13020000.0), Velocity(5800.0, 0.0)));
}

/******************************************
* CREATE STARS
* Given a number of Stars, creates and scatters them across the screen
********************************************/
void Simulator::createStars(int numStars)
{
   // Create the given number of stars
   for (int i = 0; i < numStars; i++)
   {
      // screen is 1,000 x 1,000 pixels.
      Position initial;
      initial.setPixelsX(random(-500, 500));
      initial.setPixelsY(random(-500, 500));

      this->stars.push_back(new Star(initial));
   }
};

/******************************************
* REMOVE COLLIDER
* Removes a pointer to a given Collision Object from the Simulators's collection
********************************************/
void Simulator::removeCollider(CollisionObject* removeObj) {
   // Removes the given pointer from the list
   this->collisionObjects.remove(removeObj);
};

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
      Angle shipRotation;  // The change in rotation

      // Ship turning (left and right arrows)
      if (pUI->isLeft())
         shipRotation.setRadian(-0.1);
      if (pUI->isRight())
         shipRotation.setRadian(0.1);
      ship->addRotation(shipRotation);

      // Set if the ship's thruster is on (down arrow)
      if (pUI->isDown())
         ship->setThrust(true);
      else
         ship->setThrust(false);

      if (ship->getThrust())
      {
         Velocity v;
         double accelerationTime = 30;
         v.addMeters(SHIP_ACCELERATION * accelerationTime, ship->getRotation());
         ship->addVelocity(v);
      }

      // Check for Bullet shooting (spacebar)
      if (pUI->isSpace())
         // Create a new bullet in front of the Spaceship
         createBullet(this->ship->getPosition(), this->ship->getVelocity(), this->ship->getRotation());
   }
}

/********************************************
* UPDATE
* Updates all items in the simulator, according to the amount of
* time that has passed and the affect of the Earth's gravity
*******************************************************/
void Simulator::update()
{
   // Collect all objects that are marked for destruction
   list<CollisionObject*> destroyObjsL;

   // Check for collisions between the Simulator's collisionObjects,
   //  will update the destroyed bool for any that collide
   updateCollisions();

   // For every Collision Object in the Simulator's list,
   for (CollisionObject* obj : collisionObjects)
   {
      // If it has been marked for destruction,
      //  (either from a collision or a timer expiring)
      if (obj->getDestroyed())
         // Add to list of objects to break apart
         destroyObjsL.push_back(obj);

      // Otherwise, has not been destroyed, update the Collision Object's Position
      //  (NOTE: Converts the Earth's radius from Pixels to Meters using zoom)
      else
         obj->update(this->timeDialation, this->planet->getGravity(), (this->planet->getRadius() * Position().getZoom()));
   }

   // For every Collision Object that has been marked for destruction,
   for (CollisionObject* obj : destroyObjsL)
      // Break the object apart, adding their subParts to the Simulator's list of collisionObjects
      obj->breakApart(this);

   destroyObjsL.clear(); // Clear the list of Collision Objects

   // Updates the frame of all the Stars
   for (Star* star : stars)
      star->update(this->timeDialation);
}

/******************************
* GET OBJECTS
* Creates a list of all objects in the simulator.
**************************************/
list<Object*> Simulator::getObjects() {
   // Returns the pointers for all the Objects to be drawn
   list<Object*> objects;

   // Get pointers for all the Stars
   for (Object* star : stars)
   {
      // Add a pointer to the Star (cast to Object*)
      //Object* objectP = &star;
      objects.push_back(star);
   }

   // Get pointers for all of the Collision Objects
   for(Object* obj : collisionObjects)
      // Add the Collision Object pointer (cast to Object*)
      objects.push_back(obj);

   return objects;
}

/*************************************
* UPDATE COLLISIONS
* Updates the collision of all objects in the sim by
* looping through the list of objects twice, with 
* the inner loop having one less than the outer loop.
*******************************************/
void Simulator::updateCollisions() {

   // For every Collison Object in the Simulator's collisionObjects,
   for (list<CollisionObject*>::const_iterator objOneIt = collisionObjects.begin(); objOneIt != this->collisionObjects.end(); objOneIt++)

      // Check against every object except itself
      for (list<CollisionObject*>::const_iterator objTwoIt = next(objOneIt); objTwoIt != this->collisionObjects.end(); objTwoIt++)

         // Check if the two Objects have hit eachother,
         if ((*objOneIt)->isHit(*(*objTwoIt)))

            // Tell the second object it was also hit
            (*objTwoIt)->setDestroyed(true);
};