#include "collisionObject.h"
#include "simulator.h"

void CollisionObject::breakApart(Simulator* sim)
{
	int numFragments = this->getNumFragments();
	for (int i = 0; i < numFragments; i++)
	{
		sim->addCollider(new Fragment(this->getPosition(), this->getVelocity()));
		//objects->push_back(new Fragment());
	}

	sim->removeCollider(this); // Remove pointer to self
	delete this; // Delete self
};

void CollisionObject::update(Simulator* sim) {
	// If the object has not collided,
	if (!collided)
	{
		// Calculate normally
		Object::update(TIME, GRAVITY, EARTH_RADIUS);
	}
	else
	{
		breakApart(sim);
	}

}