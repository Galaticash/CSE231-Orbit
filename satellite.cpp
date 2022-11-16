#include "satellite.h"
#include "simulator.h"

void Satellite::breakApart(Simulator* sim)
{
	/*
	// Add all parts of this Satellite
	for (vector<Part*>::iterator part = parts.begin(); part != this->parts.end(); part++)
	{
		sim->addCollider(*part);
	}*/

	// Add all the Fragments, and delete itself
	CollisionObject::breakApart(sim);
};