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
#include "uiInteract.h" // To get user input

// Objects used in the Simulator
#include "star.h"
#include "earth.h"
#include "bullet.h"
#include "spaceship.h"

// Specific types of Satellites
#include "hubble.h"
#include "starlink.h"
#include "sputnik.h"
#include "gps.h"
#include "dragon.h"

const double TIME = 48;         // Real-world seconds between frames

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

      this->timeDialation = TIME;  // Set this Simulator's time dialation

      this->debug = true; // TESTING
   };

   /*************************************
   * ADD OBJECTS
   * Adds Objects to the simulator
   ***************************************/
   void addObjects()
   {
      // Create and add the user-controlled Spaceship
      Position shipInitial = Position(); // Set Position in pixels
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
   void update();

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
   void updateCollisions(); 
};
