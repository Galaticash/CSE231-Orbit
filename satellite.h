#pragma once
/*********************************************
 * Satellite
 * An object in space that can collide with other objects in
 * space and be destroyed.
 *********************************************/

#include "collisionObject.h"
#include "part.h"

class TestSatellite;

class Satellite : public CollisionObject
{
public:
	friend TestSatellite;
	Satellite(Position pos = Position(), Velocity vel = Velocity(), double angle = 0.0) : CollisionObject(pos, vel, angle) { this->numFragments = 3; };

	vector<Part*> getSubParts() { return this->parts; };

	// TODO: Will break into Parts, pass parts
	void breakApart(vector<CollisionObject*>) { delete this; };

protected:
	vector <Part*> parts;
};