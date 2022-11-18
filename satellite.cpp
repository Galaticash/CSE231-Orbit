#include "satellite.h"
#include "simulator.h"

void Satellite::breakApart(Simulator* sim)
{	
	// The Parts this Satellite will break into
	// Translate Part pointers into CollisionObject pointers (used by Sim)
	vector<CollisionObject*> subParts;
	for(vector<Part*>::iterator it = this->parts.begin(); it != this->parts.end(); it++)
	{
		subParts.push_back(*it);
	}

	// Add all Parts to the Simulator
	addObjects(sim, subParts);

	// Add all the Fragments, and delete itself
	CollisionObject::breakApart(sim);
};