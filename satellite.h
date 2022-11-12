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
	Satellite() : Satellite(Position()) {};
	Satellite(Position pos) : Satellite(pos, Velocity()) {};
	Satellite(Position pos, Velocity vel) : CollisionObject(pos, vel) { this->numFragments = 0; };

private:
	int numFragments;
	vector <Part> parts;
};