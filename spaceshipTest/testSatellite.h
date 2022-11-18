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
		vector<CollisionObject*> getCollisionObjects() { return this->collisionObjects; };

		void clearObjects() { this->collisionObjects.clear(); this->collisionObjects = vector<CollisionObject*>{}; };
	};

	void run()
	{
		Position().setZoom(1000.0);
		// Testing number of parts broken into
		breakSubParts();

		// Testing explosion directions
		breakApartStatic();
		breakApartY();
		breakApartX();
	};

	// Check that the Satellite is breaking apart into the proper number of objects
	void breakSubParts() {
		// SETUP
		FakeSimulator fakeSim = FakeSimulator();
		fakeSim.clearObjects();

		// Can change inital Position if needed
		double initialX = 0.0;
		double initialY = 0.0;

		// Create a Satellite and get the number of Parts
		Satellite* testSatellite = new Satellite();
		
		// Set Position
		testSatellite->pos.setMeters(initialX, initialY);
		
		// Set collection of Parts
		testSatellite->parts = { new Part(), new Part() };
		
		// Count up number of Parts and number of Fragments to break into
		int expectedSubParts = testSatellite->parts.size() + testSatellite->numFragments;

		// Add the Satellite to the FakeSim and check that
		//  it is the only Object there
		fakeSim.addCollider(testSatellite);
		assert(fakeSim.getCollisionObjects().size() == 1);

		// EXERCISE - break apart the Satellite
		testSatellite->breakApart(&fakeSim);

		// VERIFY
		// Satellite has broken into the correct number of SubParts
		assert(fakeSim.getObjects().size() == expectedSubParts);
		
		// TEARDOWN	
	}

	// Check that the Satellite's subParts are set with the correct directions/velocities when the Satellite is not moving
	void breakApartStatic() {
		// SETUP 
		FakeSimulator fakeSim = FakeSimulator();
		fakeSim.clearObjects();

		// Can change inital Position if needed
		Position initialP = Position(0.0, 0.0);
		Velocity initialV = Velocity(0.0, 0.0);

		// Create a Satellite and get the number of Parts
		Satellite* testSatellite = new Satellite();

		// Set Position
		testSatellite->pos.setMeters(initialP.getMetersX(), initialP.getMetersY());
		// Set Velocity
		testSatellite->vel.setMeters(initialV.getMetersX(), initialV.getMetersY());

		// Set collection of Parts
		testSatellite->parts = { new Part(), new Part() };
		int expectedSubParts = testSatellite->parts.size() + testSatellite->numFragments;


		// Add the Satellite to the FakeSim and check that
		//  it is the only Object there
		fakeSim.addCollider(testSatellite);
		assert(fakeSim.getObjects().size() == 1);

		// EXERCISE - break apart the Satellite
		testSatellite->breakApart(&fakeSim);

		// VERIFY
		vector<CollisionObject*> collisionObjects = fakeSim.getCollisionObjects();
		assert(collisionObjects.size() == expectedSubParts);
		for (vector<CollisionObject*>::iterator it = collisionObjects.begin(); it != collisionObjects.end(); it++)
		{

		}		

		// TEARDOWN
	}

	// Check that the Satellite's subParts are set with the correct directions/velocities when the Satellite is moving in the X direction
	void breakApartX() {
		// SETUP 

		// EXERCISE

		// VERIFY

		// TEARDOWN
	}

	// Check that the Satellite's subParts are set with the correct directions/velocities when the Satellite is moving in the Y direction
	void breakApartY() {
		// SETUP 

		// EXERCISE

		// VERIFY

		// TEARDOWN
	}

};
