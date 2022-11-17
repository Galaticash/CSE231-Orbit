#include "satellite.h"
#include "simulator.h"

void Satellite::breakApart(Simulator* sim)
{	
	// The Parts this Satellite will break into
	vector<CollisionObject*> parts = { new Part() };

	// Add all Parts to the Simulator
	addObjects(sim, parts);

	// Add all the Fragments, and delete itself
	CollisionObject::breakApart(sim);
};