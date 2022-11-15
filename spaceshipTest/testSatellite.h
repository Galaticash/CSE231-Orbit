#include "TestBase.h"
#include "../Satellite.h"

class TestSatellite : public Test {

// All methods are public to share with VS test
// *Could friend VS test, but would have to look that up
public:
	void run()
	{
		Position().setZoom(1000.0);
		breakApart();
	};

	void breakApart() {
		// SETUP
		double initialX = 0.0;
		double initialY = 0.0;

		Satellite testSatellite = Satellite();
		testSatellite.pos.setMeters(initialX, initialY);
		int numParts = sizeof(testSatellite.parts);

		vector<CollisionObject*> objects;
		objects.push_back(&testSatellite);

		// EXERCISE
		testSatellite.breakApart(objects);

		// VERIFY
		// Overall Satellite is destoryed, Parts are created
		// Parts each have their own speed (randomly generated)
		// Couldn't you just assert random speed is within bounds?
		assert(sizeof(objects) == numParts);

		// Breakup Directions (stored as Angles)
		// Is there a collision Direction? Does it know from what direction the other object hit it?

		// TEARDOWN	
	}
};
