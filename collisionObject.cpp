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

/**************************
* IS HIT
* Checks if this Collision Object has hit a given Collision Object
************************************/
bool CollisionObject::isHit(const CollisionObject& other) {
   // Check if the pixels between the two objects are 
   //  less than their combined radii, destroy if colliding
   double pixelsBetween = this->pos.pixelsBetween(other.pos);
   bool collision = pixelsBetween <= (other.radius + this->radius);

   // If the Object has not already been marked for destruction,
   if (!destroyed)
      // The current collision state defines if
      //  the Object is to be destroyed
      //  (prevents true --> false error)
      this->destroyed = collision;

   // Return if this Collision Object has collided with other
   return collision;
};

/******************************************
* BREAK APART
* Creates fragments after a collision and has them
* added to the simulator's list of objects.
********************************************/
void CollisionObject::breakApart(Simulator* sim, vector<CollisionObject*> subParts)
{
	// TODO: Shorten/condense this comment section
	/* Normal Collision Objects will breakApart by removing itself
 *  from the Simulator's list of Collision Objects and deleting itself.
 *  Given a list of additional Collision Objects that this Collision Object
 *  will break apart into, otherwise assumes none */

	// Given a list of all the Collision Objects (not including Fragments)
	//  that this Collision Object will break into,
	//  (If none given, creates empty list)
	
	// For each Fragment the Collision Object will break into,
	int numFragments = this->getNumFragments();
	for (int i = 0; i < numFragments; i++)
		// Add a Fragment to list of Subparts
		subParts.push_back(new Fragment());

	// Add all Parts and Fragments to the Simulator,
	//  each with their own initial Velocity and Position
	//  so they don't crash into eachother immediately
	addObjects(sim, subParts);

	sim->removeCollider(this); // Remove pointer to self
	delete this; // Delete self
};

/******************************************
* ADD OBJECTS
* Given the Simulator and a vector of Collision Objects,
* Adds all subparts to the given Simulator's list of objects.
********************************************/
void CollisionObject::addObjects(Simulator* sim, vector<CollisionObject*> objs) {
	// For all the subparts (additional Collision Objects)
	//  that this Collision Object will break into,
	
	// Calculate the intial Velocities each subpart will have
	vector<Velocity> directions = getSubPartVel(objs.size());

	// Calculate the intial Positions of each subpart
	//  (with a buffer so they don't collide immediately)
	vector<Position> startingPos = getSubPartPos(directions);

	// Create an iterator for the Positions and Velocities
	vector<Position>::iterator pos = startingPos.begin();
	vector<Velocity>::iterator vel = directions.begin();

	// All vectors should be the same size
	assert((objs.size() == directions.size()) && (objs.size() == startingPos.size()) && (directions.size() == startingPos.size()));

	// For each subpart in the list of Collision Objects,
	for (vector<CollisionObject*>::iterator part = objs.begin(); part != objs.end(); part++)
	{
		CollisionObject* newObj = *part;

		// Set the Position and Velocity
		newObj->setPosition(*pos);
		newObj->setVelocity(*vel);

		// Add the Collision Object to the Simulator
		sim->addCollider(newObj);

		// Move to the next item in the position and velocity vectors
		pos++;
		vel++;
	}
}

/******************************************
* GET SUB PART VELOCITY
* Calculates the Velocity of created subParts
* given the total number of Parts and Fragments.
********************************************/
vector<Velocity> CollisionObject::getSubPartVel(int subParts) {
	vector<Velocity> velocities;

	// For each subPart, create a random velocity for it to travel
	for (int i = 0; i < subParts; i++)
	{
		// Copy the initial velocity
		Velocity newVel = Velocity(this->vel);
		
		// Copy the initial direction/angle
		Angle newAngle = Angle(newVel.getAngle().getRadian());

		// Give each subPart a slightly different angle from the initial
		// Ex: +1/4PI, +2/4PI... etc or 1/3PI + 2/3PI.. etc
		newAngle += Angle(((i * PI) / (subParts + numFragments)));

		// Add bewteen 5000 and 9000 m/s to this subPart's velocity
		newVel.addMeters(random(5000.0, 9000.0), newAngle);

		// Add to the vector of Velocities to give the subParts
		velocities.push_back(newVel);
	}

	return velocities;
}

/******************************************
* GET SUB PART POSITION
* Calculates the Position of created subParts
* given the total number of Parts and Fragments.
********************************************/
vector<Position> CollisionObject::getSubPartPos(vector<Velocity> directions) {
	vector<Position> positions;

	// For each direction given, create a Position 4 pixels in that direction
	for (vector<Velocity>::iterator it = directions.begin(); it != directions.end(); it++)
	{
		// Starting at the original Collision Object's position,
		Position newPos = Position(this->pos);

		// Have each object move 4 pixels in direction of travel.		
		double buffer = 20; // Default 4
		
		// ERROR: Parts are colliding immediately
		// TESTING: -1, maybe they were going together then apart?

		Angle direction = (*it).getAngle();
		direction *= -1.0;
		
		// Find X and Y from Angle of the current Velocity
		newPos.addPixels(buffer, direction);

		// Add to the vector of Positions to give the subParts
		positions.push_back(newPos);
	}

	return positions;
}