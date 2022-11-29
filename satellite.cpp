#include "satellite.h"
#include "simulator.h"

/*
	NOTE: This version makes Satellite class unecessary, just use CollisionObject's version
	No real uniqueness about Satellite, only the 'types' of Satellites act differently
	(But just calling CollisionObject::breakApart() with different subParts parameters)
*/

void Satellite::breakApart(Simulator* sim, vector<CollisionObject*> subParts)
{	
	// Given a list of all the Parts this Satellite will break into,
	//  where each type of Satellite has its own unique Parts list

	// Add all the Fragments (from numFragments), 
	//  add them to the simulator, then delete self
	CollisionObject::breakApart(sim, subParts);
};