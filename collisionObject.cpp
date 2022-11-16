#include "collisionObject.h"
#include "simulator.h"

void CollisionObject::breakApart(Simulator* sim)
{
	int numFragments = this->getNumFragments();
	for (int i = 0; i < numFragments; i++)
	{
		sim->addCollider(new Fragment());
		//objects->push_back(new Fragment());
	}

	sim->removeCollider(this); // Remove pointer to self
	delete this; // Delete self
};