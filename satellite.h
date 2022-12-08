/***********************************************************************
 * Header File:
 *    Satellite : An object in the orbital simulator that breaks into
 *		parts and/or fragments.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Each satellite can become defunct and need destroyed, except for 
 *		the spaceship the user controls.
 ************************************************************************/
#pragma once
#include "part.h"

class TestSatellite; // For test Cases

#ifndef DEFECTIVE_VARIABLES
#define DEFECTIVE_VARIABLES
// 1 in 10,000 creates a good amount of time between different satellites becoming defective.
const int DEFECTIVE_CHANCE = 10000;

// The amount of spin added to a defective Satellite
const double DEFECTIVE_SPIN_ANGLE = 0.1;
#endif

/*********************************************
 * Satellite
 * An object in space that can collide with other objects in
 * space and be destroyed.
 *********************************************/
class Satellite : public CollisionObject
{
public:
	friend TestSatellite; // For test cases

	Satellite(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CollisionObject(pos, vel, angle) 
	{ 
		this->radius = 10;		// The Collision Object's radius in pixels
		this->numFragments = 2; // The number of Fragments to break apart into
		this->defective = 0;		// Satellites aren't initially defective
	};

	/******************************************
	* UPDATE
	* Updates the position and velocity of the Object
	* Satellites that are defective will spin, and those
	* that aren't defective have a random chance to beceome defective
	********************************************/
	virtual void update(double time, double gravity, double planetRadius) {
		// If the Satellite is defective,
		if (defective)
			// Add defective spin to the Satellite
			this->rotationAngle += DEFECTIVE_SPIN_ANGLE;
		else
			// Has a random chance of becoming defective when running the sim.
			defective = random(0, DEFECTIVE_CHANCE) == DEFECTIVE_CHANCE - 1 ? true : false;

		// Then update normally
		CollisionObject::update(time, gravity, planetRadius);
	}

	// The Satellite will break into Parts (depends on type of Satellite: Hubble, Starlink)
	virtual void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {})
	{
		// Given a list of all the Parts this Satellite will break into,
		//  where each type of Satellite has its own unique Parts list

		// Add all the Parts and Fragments (from numFragments), 
		//  to the simulator, then delete self
		CollisionObject::breakApart(sim, subParts);	
	}

protected:
	bool defective;	// If the Satellite will be given a defective spin
};