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

/*
	NOTE: This version makes Satellite class unecessary
	No real uniqueness about Satellite, only the 'types' of Satellites act differently
	(Just calling CollisionObject::breakApart() with different subParts parameters)
*/

/*
void Satellite::breakApart(Simulator* sim, vector<CollisionObject*> subParts)
{	
	// Given a list of all the Parts this Satellite will break into,
	//  where each type of Satellite has its own unique Parts list

	// Add all the Parts and Fragments (from numFragments), 
	//  to the simulator, then delete self
	CollisionObject::breakApart(sim, subParts);
};*/