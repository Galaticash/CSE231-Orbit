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

class TestSatellite;

// The amount of spin added to a defective Satellite
#ifndef DEFECTIVE_SPIN
#define DEFECTIVE_SPIN
const double DEFECTIVE_SPIN_ANGLE = 0.1;
#endif

// 1 in 5,000 creates a good amount of time between different satellites becoming defective.
const int DEFECTIVE_CHANCE = 5000;

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
		this->radius = 10; // The Collision Object's radius in pixels
		this->numFragments = 2;		// The number of Fragments to break apart into
		this->defective = 0;	// Randomly deciedes if the Satellite will spin (overriden for Ship)
	};

	virtual void update(double time, double gravity, double planetRadius);

	/* TODO: Uses Collision Object's version, not needed? UPDATE: It's not needed
	// The Satellite will break into Parts (depends on type of Satellite: Hubble, Starlink)
	virtual void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {})
	{
		// Given a list of all the Parts this Satellite will break into,
		//  where each type of Satellite has its own unique Parts list

		// Add all the Parts and Fragments (from numFragments), 
		//  to the simulator, then delete self
		CollisionObject::breakApart(sim, subParts);	
	}
	*/
protected:
	bool defective;	// If the Satellite will be given a defective spin
};