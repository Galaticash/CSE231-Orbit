#include "TestBase.h"
#include "../Satellite.h"
#include "../simulator.h"

class TestSatellite : public Test {

// All methods are public to share with VS test
// *Could friend VS test, but would have to look that up
public:

	class DummySimulator : public Simulator {
	public:
		DummySimulator() {}; // Doesn't create Ship or Earth

		// addCollider and removeCollider act as normal
		//  used to tell if breakApart works

		// Only testing Satellite, no Stars, Ship, or Bullets
		void createStars() { assert(false);  };
		void createBullet(Position pos, Velocity vel, double angle) { assert(false); };
		void moveShip(double x, double y) { assert(false); };
	
		// TODO: update in Simulator should take no arguements,
		//  the parameters are for testing purposes only (custom time, gravity on/off)
	};

	class FakeSimulator : public DummySimulator {
	public:
		FakeSimulator() {};

		// Only update Collision Objects
		void update(double t = TIME, bool gravityOn = true)
		{
			vector<CollisionObject*> colliders = getCollisions();

			// For every object that collided,
			for (vector<CollisionObject*>::iterator it = colliders.begin(); it != colliders.end(); it++)
			{
				// Break the object apart, adding subParts to the Simulator's list of collisionObjects
				CollisionObject* obj = *it;
				obj->breakApart(this);
			}
			colliders.clear();

			/* Ignore stars */

			// Update the position of each CollisionObject
			for (vector<CollisionObject*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
			{
				CollisionObject* obj = *it;

				// If gravity is turned off, passes 0 values
				double gravity = gravityOn ? GRAVITY : 0.0;
				double radius = gravityOn ? EARTH_RADIUS : 0.0;
				obj->update(t, gravity, radius);
			}

		};
		vector<Object*> getObjects() {
			// Returns the pointers for all the Objects to be drawn
			vector<Object*> objects;

			/* Ignores Stars */

			// Translates CollisionObject pointers into Object Pointers
			for (vector<CollisionObject*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
			{
				objects.push_back(*it);
			}
			return objects;
		};
	
		void clearObjects() { this->collisionObjects.clear(); this->collisionObjects = vector<CollisionObject*>{}; };
	};


	void run()
	{
		Position().setZoom(1000.0);
		breakApart();
	};

	// Check that the
	void breakApart() {
		// SETUP
		FakeSimulator fakeSim = FakeSimulator();
		fakeSim.clearObjects();

		// Can change inital Position if needed
		double initialX = 0.0;
		double initialY = 0.0;

		// Create a Satellite and get the number of Parts
		Satellite* testSatellite = new Satellite();
		testSatellite->pos.setMeters(initialX, initialY);
		int numParts = sizeof(testSatellite->parts);
		int numFragments = testSatellite->numFragments;
		int expectedSubParts = numParts + numFragments;

		// Add the Satellite to the FakeSim and check that
		//  it is the only Object there
		fakeSim.addCollider(testSatellite);
		assert(fakeSim.getObjects().size() == 1);

		// EXERCISE
		testSatellite->breakApart(&fakeSim);

		// VERIFY
		// Satellite has broken into SubParts
		assert(fakeSim.getObjects().size() == expectedSubParts);
		
		// Overall Satellite is destroyed, Parts are created
		// Parts each have their own speed (randomly generated)
		// Couldn't you just assert random speed is within bounds?

		// Breakup Directions (stored as Angles)
		// Is there a collision Direction? Does it know from what direction the other object hit it?

		// TEARDOWN	
	}
};
