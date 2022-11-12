#pragma once

#include "spaceship.h"
#include "star.h"
#include "earth.h"


//const double GRAVITY = -9.8067;           // Gravity constant in m/s^2
//const double EARTH_RADIUS = 6378000.0;    // meters


const double PI = 3.1415926;            // The value of Pi

// Simulation Information
// TODO: I'm sure there's a better way to calculate framerate
//  (maybe using gl's framerate or something), but this will do for now
const double FPS = 30;          // The number of frames drawn per second          
const double TIME = 48;         // Real-world seconds between frames
const double TIME_DILATION = 24 * 60;    // One minute in simulator = One day in real world

// Planet Information
const double SECONDS_DAY = 24 * 60 * 60; // 24 hours * 60 minutes * 60 seconds
const double ROTATION_SPEED = -(2 * PI / FPS) * TIME_DILATION / SECONDS_DAY;

// Constants for GEO Orbit
const double GEO_HEIGHT = 35786000.0 + EARTH_RADIUS; // GEO orbit, items here should match Earth's rotation
const double GEO_VELOCITY_X = -3100.0;  // moving 3.1 km/s (to the left in this example)


class Simulator {
public:
	Simulator()
	{
		this->Ship = new Spaceship();
		addCollider(Ship); // Add to the list of Collision Objects
		addCollider(new Earth()); // Create an Earth and add it to the list of Collision Objects
	
	};
	void createStars() { /* For numStars, add new Star() to list of Stars */ };
	void addCollider(CollisionObject* newObj) { this->collisionObjects.push_back(newObj); };

	void moveShip(double x, double y) {};

	void update() {}; /* For object in collisionObjs, update their position (according to the amount of time that has passed? Better to leave with Simulator instead of assuming all object will have the correct time*/

	vector<Object*> getObjects(); // Get all Objects to be drawn


private:
	vector<CollisionObject*> collisionObjects;
	Spaceship* Ship;
	vector<Star> stars;
	double timeDialation;

};