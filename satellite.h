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
	Satellite(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : CollisionObject(pos, vel, angle) { this->numFragments = 2; this->radius = 1000000.0; };

	// The Satellite will break into Parts (depending on type of Satellite: Hubble, Starlink)
	void breakApart(Simulator* sim); 
};