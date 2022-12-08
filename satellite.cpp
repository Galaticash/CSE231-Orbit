/***********************************************************************
 * Source File:
 *    Satellite : An object in the orbital simulator that breaks into
 *		parts and/or fragments.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Each satellite can become defunct and need destroyed, except for
 *		the spaceship the user controls.
 ************************************************************************/
#include "satellite.h"
#include "simulator.h"

/*****************************
* UPDATE
* Updates the satellite's defective status 
* and adds rotation based on defective status, 
* then proceeds to update the object as normal.
***********************************/
void Satellite::update(double time, double gravity, double planetRadius) {
	// Becomes defective at a random time when running the sim.
	if (!defective)
		defective = random(0, DEFECTIVE_CHANCE) == DEFECTIVE_CHANCE - 1 ? true : false;

	// If the Satellite is defective,
	if (defective)
	{
		// Add defective spin to the Satellite divided by simulator time.
		this->rotationAngle += DEFECTIVE_SPIN_ANGLE / 48;
	}

	// Then update normally
	CollisionObject::update(time, gravity, planetRadius);
}