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

/*
#ifndef DEFECTIVE_SPIN
#define DEFECTIVE_SPIN
double DEFECTIVE_SPIN_ANGLE = 10.0;
#endif
*/

/*********************************************
 * Satellite
 * An object in space that can collide with other objects in
 * space and be destroyed.
 *********************************************/
class Satellite : public CollisionObject
{
public:
	friend TestSatellite;
	Satellite(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CollisionObject(pos, vel, angle) 
	{ 
		this->numFragments = 2; 
		this->radius = 10; // The Collision Object's radius in pixels

		this->defective = false;  // If the Satellite will spin
	};

	void update(double time, double gravity, double planetRadius) {
		// If the Satellite is defective,
		if (defective)
		{
			double DEFECTIVE_SPIN_ANGLE = 1.0;
			// Add defective spin to the Satellite
			this->rotationAngle += DEFECTIVE_SPIN_ANGLE;
		}

		// Then update normally
		CollisionObject::update(time, gravity, planetRadius);
	}

	// The Satellite will break into Parts (depending on type of Satellite: Hubble, Starlink)
	virtual void breakApart(Simulator* sim, vector<CollisionObject*> subParts = {});

protected:
	bool defective;

};