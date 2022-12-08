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