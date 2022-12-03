/***********************************************************************
 * Header File:
 *    Simulator : Runs the main interactions in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Keeps track of the objects in the simulation and is in charge of
 *		creating new objects, updating the game, getting inputs, and checking
 *		for collisions between objects.
 ************************************************************************/
#pragma once
#include "uiInteract.h"
#include "star.h"
#include "earth.h"
#include "bullet.h"
#include "uiDraw.h"		// For Random

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


class Simulator {
public:
	Simulator()
	{
		addObjects();  // Create all Collision Objects (Earth, Spaceship, Satellites, etc)
		//addTestObjects();

		createStars(500); // Create a given number of Stars

		this->timeDialation = TIME;
	};


	/*************************************
	* ADD TEST OBJECTS
	* TESTING: Adds additional Objects to the simulator
	***************************************/
	void addTestObjects()
	{
		// Parts don't appear since they collide too fast
		addCollider(new HubbleTelescope(Position(-46500000.13, 21000000.0), Velocity(2000.0, 2684.68)));
	}

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

		/* Test Objects */

		/*
		addCollider(new Hubble(Position(0.0, GEO_HEIGHT), Velocity(-3100.0, 0.0)));

		addCollider(new StarlinkBody(Position(-10888386.068, 40737174.459), Velocity(-3100.0, 0.0)));

		// Added quicker collision
		addCollider(new Hubble(Position(-13595100.4029, 39923965.84268), Velocity(2938.822, 984.102)));

		addCollider(new Starlink(Position(-GEO_HEIGHT, 0.0), Velocity(0.0, 3100.0)));
		addCollider(new HubbleLeft(Position(0.0, -GEO_HEIGHT), Velocity(0.0, 3000.0)));
		addCollider(new Hubble(Position(GEO_HEIGHT, -GEO_HEIGHT), Velocity(-3100.0, 0.0)));
		
		addCollider(new HubbleLeft(Position(-15000000.4029, -39000000.84268), Velocity(-3100.0, 0.0)));
		addCollider(new HubbleLeft(Position(-13595100.4029, -40000000.84268), Velocity(-3100.0, 0.0)));
		*/

		/* Actual Objects to add */
		
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

	void createStars(int numStars) 
	{
		// Create the given number of stars
		// TODO: Randomly scatter through sky or make a pattern
		for (int i = 0; i < numStars; i++)
		{
			// screen is 1,000 x 1,000 pixels. 
			int posX = random(-500, 500);
			int posY = random(-500, 500);
			Position initial;
			//initial.setPixelsX(-250.0);
			//initial.setPixelsY(100 * i);
			initial.setPixelsX(posX);
			initial.setPixelsY(posY);
			this->stars.push_back(Star(initial));
		}
	};

	// Add and Remove Collision Objects from the Simulators's collection
	void addCollider(CollisionObject* newObj) { this->collisionObjects.push_back(newObj); };
	void removeCollider(CollisionObject* removeObj) { 
		// If the given pointer is in the vector, remove it
		vector<CollisionObject*>::iterator removeIt = find(collisionObjects.begin(), collisionObjects.end(), removeObj);
		if (removeIt != collisionObjects.end())
		{
			//delete* removeIt; // Not in charge of deleting the object
			this->collisionObjects.erase(removeIt);
		}
	};

	// Creates a Bullet in front of the Simulator's Spaceship
	void createBullet(Position pos, Velocity vel, Angle angle) 
	{
		this->collisionObjects.push_back(new Bullet(pos, vel, angle));	
	};
	
	// Gets input from the user that affects the Simulation
	void getInput(const Interface* pUI);

	// Updates all items in the simulator, according to the amount of
	//   time that has passed and the affect of the Earth's gravity
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
			{
				// Add to list of objects to break apart
				destroyObjs.push_back(*it);
			}

			// Otherwise, has not been destroyed, update Position
			else
			{
				// Update the position of the Collision Object
				//   given the time passed, gravity, and Earth's radius.
				//   Convert the Earth's radius from Pixels to Meters
				(*it)->update(this->timeDialation, this->planet->getGravity(), (this->planet->getRadius() * DEFAULT_ZOOM));
			}
		}

		// For every Collision Object that has been marked for destruction,
		for (vector<CollisionObject*>::iterator it = destroyObjs.begin(); it != destroyObjs.end(); it++)
		{
			// Break the object apart, adding their subParts to the Simulator's list of collisionObjects
			CollisionObject* obj = *it;

			// DEBUG: What objects have been destroyed
			string objType = typeid(*obj).name();
			cout << objType << " destroyed" << endl;

			obj->breakApart(this);
		}
		destroyObjs.clear();

		// Updates the frame of all the Stars
		for (vector<Star>::iterator it = this->stars.begin(); it != this->stars.end(); it++)
		{
			(*it).update(this->timeDialation);
		}
	}

	vector<Object*> getObjects(); // Get all Objects to be drawn

protected:
	vector<CollisionObject*> collisionObjects;	// All Objects that can collide
	Spaceship* ship;	// The user-controlled Spaceship
	Earth* planet;		// The planet at the center of the Simulation
	vector<Star> stars;	// All the stars to display
	double timeDialation;// Real-world seconds between frames

	void updateCollisions() {
		// DEGBUG: Checking efficiency of algorithm
		//int outerCount = 0; // 12 <-- 12 Objects total
		//int innerCount = 0; // 66 <-- comparisons (12 + 11 + 10 + 9..)

		// For every Collison Object in the Simulator's collisionObjects,
		for (vector<CollisionObject*>::iterator objOneIt = this->collisionObjects.begin(); objOneIt != this->collisionObjects.end(); objOneIt++)
		{
			//outerCount++;
			// Check against every object except itself
			for (vector<CollisionObject*>::iterator objTwoIt = objOneIt + 1; objTwoIt != this->collisionObjects.end(); objTwoIt++)
			{
				//innerCount++;
				if (!(*objOneIt)->getDestroyed() && !(*objTwoIt)->getDestroyed())
				{
					// Check if the two Objects have hit eachother,
					if ((*objOneIt)->isHit(*(*objTwoIt)))
					{
						// Tell the second object it was also hit
						(*objTwoIt)->setDestroyed(true);
					}
				}
				// If ObjOne has not been hit, but ObjTwo has already been hit,
				else if ((!(*objOneIt)->getDestroyed() && (*objTwoIt)->getDestroyed()))
				{
					// Check if ObjOne has been hit, updates destroy bool
					(*objOneIt)->isHit(*(*objTwoIt));					
				}
				// If ObjOne has not been hit, but ObjTwo has already been hit,
				else if ((!(*objTwoIt)->getDestroyed() && (*objOneIt)->getDestroyed()))
				{
					// Check if ObjTwo has been hit, updates destroy bool
					(*objTwoIt)->isHit(*(*objOneIt));
				}
			}
		}
	};
};
