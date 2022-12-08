/***********************************************************************
 * Header File:
 *    Simulator : Runs the main interactions in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Keeps track of the objects in the simulation and is in charge of
 *		creating new objects, updating the sim, getting inputs, and checking
 *		for collisions between objects.
 ************************************************************************/
#pragma once
#include "uiInteract.h"
#include "star.h"
#include "earth.h"
#include "bullet.h"

// Specific types of Satellites
#include "spaceship.h"
#include "hubble.h"
#include "starlink.h"
#include "sputnik.h"
#include "gps.h"
#include "dragon.h"

// Simulation Information
const double TIME = 48;         // Real-world seconds between frames

// Constants for GEO Orbit
const double GEO_HEIGHT = 35786000.0 + EARTH_RADIUS; // GEO orbit, items here should match Earth's rotation
const double GEO_VELOCITY_X = -3100.0;  // moving 3.1 km/s (to the left in this example)

/*********************************************
 * Simulator
 * Handles running the orbital simulation.  
 *********************************************/
class Simulator {
public:
   Simulator()
   {
	   addObjects();  // Create all Collision Objects (Earth, Spaceship, Satellites, etc)

      createStars(500); // Create a given number of Stars

      this->timeDialation = TIME;
   };

   /*************************************
   * ADD OBJECTS
   * Adds Objects to the simulator
   ***************************************/
   void addObjects()
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
   void createStars(int numStars) 
   {
      // Create the given number of stars
      for (int i = 0; i < numStars; i++)
      {
         // screen is 1,000 x 1,000 pixels.
         Position initial;
         initial.setPixelsX(random(-500, 500));
         initial.setPixelsY(random(-500, 500));
         
         this->stars.push_back(Star(initial));
      }
   };

   /******************************************
   * ADD COLLIDER
   * Adds a pointer to a given Collision Object to the Simulators's collection
   ********************************************/
   void addCollider(CollisionObject* newObj) { this->collisionObjects.push_back(newObj); };
   
   /******************************************
   * REMOVE COLLIDER
   * Removes a pointer to a given Collision Object from the Simulators's collection
   ********************************************/
   void removeCollider(CollisionObject* removeObj) { 
      // If the given pointer is in the vector, remove it
      vector<CollisionObject*>::iterator removeIt = find(collisionObjects.begin(), collisionObjects.end(), removeObj);
      if (removeIt != collisionObjects.end())
      {
         //delete* removeIt; // Not in charge of deleting the object
         this->collisionObjects.erase(removeIt);
      }
   };

   /******************************************
   * CREATE BULLET
   * Creates a Bullet in front of the Simulator's Spaceship
   ********************************************/
   void createBullet(Position pos, Velocity vel, Angle angle) 
   {
      this->collisionObjects.push_back(new Bullet(pos, vel, angle));	
   };
	
   /******************************************
   * GET INPUT
   * Gets input from the user that affects the Simulation
   ********************************************/
   void getInput(const Interface* pUI);

   /******************************************
   * UPDATE
   * Updates all items in the simulator, according to the amount of
   * time that has passed and the affect of Earth's gravity
   ********************************************/
   void update()
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

   vector<Object*> getObjects(); // Get all Objects to be drawn

   bool getDebug() { return this->debug; }; // DEBUG: Returns if debugging features should be shown

protected:
   vector<CollisionObject*> collisionObjects;	// All Objects that can collide
   Spaceship* ship;	   // The user-controlled Spaceship
   Earth* planet;		   // The planet at the center (0, 0) of the Simulation
   vector<Star> stars;	// All the stars to display
   double timeDialation;// Real-world seconds between frames

   bool debug; // Toggle Debugging features on/off

   /******************************************
   * UPDATE COLLISIONS
   * Checks for collisions between this Simulator's collisionObjects
   ********************************************/
   void updateCollisions() {
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
