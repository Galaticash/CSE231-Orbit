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
   void addObjects();

   /******************************************
   * CREATE STARS
   * Given a number of Stars, creates and scatters them across the screen
   ********************************************/
   void createStars(int numStars);

   /******************************************
   * ADD COLLIDER
   * Adds a pointer to a given Collision Object to the Simulators's collection
   ********************************************/
   void addCollider(CollisionObject* newObj) { this->collisionObjects.push_back(newObj); };
   
   /******************************************
   * REMOVE COLLIDER
   * Removes a pointer to a given Collision Object from the Simulators's collection
   ********************************************/
   void removeCollider(CollisionObject* removeObj);

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
