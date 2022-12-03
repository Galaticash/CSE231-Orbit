/***********************************************************************
 * Source File:
 *    CollisionObject : An object in the orbital simulator that has collision.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Deals with any object that has collision. Detects collisions, deletes
 *		object, and creates new ones when applicable. Earth is included because
 *		it can collide even though it is not destroyed.
 ************************************************************************/
#include "collisionObject.h"
#include "simulator.h"

/******************************************
* BREAK APART
* Creates fragments after a collision and has them
* added to the simulator's list of objects.
********************************************/
void CollisionObject::breakApart(Simulator* sim, vector<CollisionObject*> subParts)
{
	// Given a list of all the Collision Objects 
	//  that this Collision Object will break into,
	//  (If none given, creates empty list)

	// For each fragment the Collision Object will break into,
	int numFragments = this->getNumFragments();
	for (int i = 0; i < numFragments; i++)
	{
		// Add a Fragment to list of SubParts
		subParts.push_back(new Fragment());
	}

	// Add all Parts and Fragments to the Simulator
	// Fragments and Parts will go in different directions
	addObjects(sim, subParts);

	sim->removeCollider(this); // Remove pointer to self
	delete this; // Delete self
};

/******************************************
* ADD OBJECTS
* Creates fragments after a collision and adds
* fragments and parts to simulator's list of objects.
********************************************/
void CollisionObject::addObjects(Simulator* sim, vector<CollisionObject*> obj) {
	// For each sub Object the Collision Object will break into,
	
	// Calculate the different Velocities each Part will travel
	vector<Velocity> directions = getSubPartVel(obj.size());

	// Calculate different intial Positions of each Part
	vector<Position> startingPos = getSubPartPos(directions);

	// Add all Collision Objects, each going in different directions
	vector<Position>::iterator pos = startingPos.begin();
	vector<Velocity>::iterator vel = directions.begin();

	// All vectors should be the same size
	assert((obj.size() == directions.size()) && (obj.size() == startingPos.size()) && (directions.size() == startingPos.size()));

	// For each CollisionObject,
	for (vector<CollisionObject*>::iterator part = obj.begin(); part != obj.end(); part++)
	{
		CollisionObject* newObj = *part;

		// Set the Position and Velocity
		newObj->setPosition(*pos);
		newObj->setVelocity(*vel);

		// Add the Collision Object to the Simulator
		sim->addCollider(newObj);

		// Move to the next item in each vector
		pos++;
		vel++;
	}
}

/******************************************
* GET SUB PART VEL
* Calculates the new velocity for a 
* collection of parts and fragments.
********************************************/
vector<Velocity> CollisionObject::getSubPartVel(int subParts) {
	vector<Velocity> velocities;

	// For each subPart, create a random velocity for it to travel
	for (int i = 0; i < subParts; i++)
	{
		// Initial direction
		Velocity newVel = Velocity(this->vel);
		
		// Figure out which direction to add the Velocity
		// Based on the original CollisionObject's Velocity
		Angle newAngle = Angle(newVel.getAngle().getRadian());

		Angle difference = Angle(((i * PI) / subParts));
		//Angle((PI + (i * PI) / subParts));

		// Plus a direction from the number of subParts
		newAngle += difference; // Ex: +1/4PI, +2/4PI... etc or 1/3PI + 2/3PI.. etc

		// Add 5000 - 9000 m/s to speed
		//double extraSpeed = random(5000, 9000);
		newVel.addMeters(6000.0, newAngle); // TODO: Add random

		velocities.push_back(newVel);
	}

	return velocities;
}

/******************************************
* GET SUB PART POS
* Calculates the new position for a
* collection of parts and fragments.
********************************************/
vector<Position> CollisionObject::getSubPartPos(vector<Velocity> directions) {
	vector<Position> positions;

	// For each direction given, create a Position 4 pixels in that direction
	for (vector<Velocity>::iterator it = directions.begin(); it != directions.end(); it++)
	{
		// Starting at the original Collision Object's position,
		Position newPos = Position(this->pos);

		// 4 pixels in direction of travel
		// Find X and Y from Angle of the current Velocity
		double buffer = 4; // Default 4
		newPos.addPixels(buffer, (*it).getAngle());

		positions.push_back(newPos);
	}

	return positions;
}