#include "collisionObject.h"
#include "simulator.h"

void CollisionObject::breakApart(Simulator* sim)
{
	// For each fragment the Collision Object will break into,
	int numFragments = this->getNumFragments();

	// Create a vector with all the Fragments
	vector<CollisionObject*> fragments;
	for (int i = 0; i < numFragments; i++)
	{
		fragments.push_back(new Fragment());
	}
	
	addObjects(sim, fragments);

	sim->removeCollider(this); // Remove pointer to self
	delete this; // Delete self
};

void CollisionObject::addObjects(Simulator* sim, vector<CollisionObject*> obj) {
	// For each sub Object the Collision Object will break into,
	
	// Calculate the different velocities each Part will travel
	vector<Velocity> directions = getSubPartVel(obj.size());

	// Calculate different intial positions of each Part
	vector<Position> startingPos = getSubPartPos(directions);

	// Add all parts of this Satellite, going in different directions
	vector<Position>::iterator pos = startingPos.begin();
	vector<Velocity>::iterator vel = directions.begin();

	// All vectors should be the same size (commented out, cassert not here)
	assert((obj.size() == directions.size()) && (obj.size() == startingPos.size()) && (directions.size() == startingPos.size()));

	// For each CollisionObject,
	for (vector<CollisionObject*>::iterator part = obj.begin(); part != obj.end(); part++)
	{
		CollisionObject* newObj = *part;
		newObj->setPosition(*pos);
		newObj->setVelocity(*vel);

		sim->addCollider(newObj);

		// Move to the next item in each vector
		pos++;
		vel++;
	}
}

vector<Velocity> CollisionObject::getSubPartVel(int subParts) {
	vector<Velocity> velocities;

	// For each subPart, create a random velocity for it to travel
	for (int i = 0; i < subParts; i++)
	{
		// Initial direction
		Velocity newVel = Velocity(this->vel);

		// Add 5000 - 9000 m/s to speed, random direction
		// Will use 6000 currenlty
		newVel.addMeters(6000.0, newVel.getAngle());

		velocities.push_back(newVel);
	}

	return velocities;
}

vector<Position> CollisionObject::getSubPartPos(vector<Velocity> directions) {
	vector<Position> positions;

	// For each direction given, create a Position 4 pixels in that direction
	for (vector<Velocity>::iterator it = directions.begin(); it != directions.end(); it++)
	{
		// Starting at the original Collision Object's position,
		Position newPos = Position(this->pos);

		// 4 pixels in direction of travel
		// Find x and Y from Velocity
		//newPos.addPixelsX(4);

		positions.push_back(newPos);
	}

	return positions;
}