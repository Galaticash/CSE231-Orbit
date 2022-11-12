#pragma once

#include "collisionObject.h"
#include "part.h"

/*********************************************
 * Satellite
 * An object in space that can collide with other objects in 
 * space and be destroyed. 
 *********************************************/
class Satellite : public CollisionObject
{
public:
	// Constructors
	Satellite(Position pos = Position(), Velocity vel = Velocity(), double angle = 0.0) : CollisionObject(pos, vel, angle) { this->numFragments = 0; };

protected:
	int numFragments;
	vector <Part> parts;
};