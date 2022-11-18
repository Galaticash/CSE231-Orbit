#pragma once

#include "part.h"

class TestSatellite;

/*********************************************
 * Satellite
 * An object in space that can collide with other objects in
 * space and be destroyed.
 *********************************************/
class Satellite : public CollisionObject
{
public:
	friend TestSatellite;
	Satellite(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CollisionObject(pos, vel, angle) { this->numFragments = 1; this->radius = 1000000.0; };

	//void setSubParts(vector<Part*> newParts) { this->parts.clear(); this->parts = newParts; };
	vector<Part*> getSubParts() { return this->parts; };

	void breakApart(Simulator* sim);

protected:
	vector <Part*> parts;
};