#include "satellite.h"
#include "simulator.h"

void Satellite::breakApart(Simulator* sim)
{	
	// The Parts this Satellite will break into
	// Assumes 2 random Parts
	vector<CollisionObject*> subParts = { new Part(), new Part() };

	// Add all Parts to the Simulator
	addObjects(sim, subParts);

	// Add all the Fragments, and delete itself
	CollisionObject::breakApart(sim);
};