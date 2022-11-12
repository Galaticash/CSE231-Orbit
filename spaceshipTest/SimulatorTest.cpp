/***************************************
* Simulation Test
*
*
************************************/
#include "pch.h"
#include "CppUnitTest.h"
#include "../simulator.h"
#include "../satellite.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SatelliteTest
{
	TEST_CLASS(SimulatorTest)
	{
	public:
		// Tolerance of floating point approximation
		const double tolerance = 100.0;

		const double GRAVITY_TEST_TIME = 10;
		const double GRAVITY_DISTANCE = 40000000.0;

		// utility funciton because floating point numbers are approximations
		bool closeEnough(double value, double test, double tolerence) const
		{
			double difference = value - test;
			return (difference >= -tolerence) && (difference <= tolerence);
		}
		
		TEST_METHOD(SimulatorTesting)
		{
			// The Simulator's objects are affected by gravity
			GravityDown();
			GravityUp();
			GravityLeft();
			GravityRight();

			// The Simultaor can properly detect collisions
			CollisionHeadOn();
			CollisionMeeting();
			CollisionTBone();

			// A Satellite can properly orbit in the Simulation
			GEO_Orbit();
		}

		TEST_METHOD(GravityDown)
		{
			// SETUP - Place a Satelite above the Earth
			Simulator test = Simulator();

			Position initial = Position();
			double initialX = 0.0;
			double initialY = GRAVITY_DISTANCE;
			initial.setMeters(initialX, initialY);

			Satellite testSatellite = Satellite(initial);
			test.addCollider(&testSatellite);

			// EXERCISE - Update Simulation
			test.update(GRAVITY_TEST_TIME);

			// VERIFY - Satelite should accelerate down
			// Make sure x didn't move (approximate for floating point)			
			Assert::IsTrue(closeEnough(initialX, testSatellite.getPosition().getMetersX(), tolerance));
			// Satelite should move down
			Assert::IsTrue(initialY > testSatellite.getPosition().getMetersY());

			// TEARDOWN
		}

		TEST_METHOD(GravityUp)
		{
			// SETUP - Place a Satelite beneath the Earth
			Simulator test = Simulator();

			Position initial = Position();
			double initialX = 0.0;
			double initialY = -GRAVITY_DISTANCE;
			initial.setMeters(initialX, initialY);

			Satellite testSatellite = Satellite(initial);
			test.addCollider(&testSatellite);

			// EXERCISE - Update Simulation
			test.update(GRAVITY_TEST_TIME);

			// VERIFY - Satelite should accelerate down
			// Make sure x didn't move (approximate for floating point)			
			Assert::IsTrue(closeEnough(initialX, testSatellite.getPosition().getMetersX(), tolerance));
			// Satelite should move up
			Assert::IsTrue(initialY < testSatellite.getPosition().getMetersY());

			// TEARDOWN
		}

		TEST_METHOD(GravityLeft)
		{
			// SETUP -  Place a Satelite to the right of Earth
			Simulator test = Simulator();

			Position initial = Position();
			double initialX = GRAVITY_DISTANCE;
			double initialY = 0.0;
			initial.setMeters(initialX, initialY);

			Satellite testSatellite = Satellite(initial);
			test.addCollider(&testSatellite);

			// EXERCISE - Update Simulation
			test.update(GRAVITY_TEST_TIME);

			// VERIFY - Satelite should accelerate down
			// Make sure y didn't move (approximate for floating point)			
			Assert::IsTrue(closeEnough(initialY, testSatellite.getPosition().getMetersY(), tolerance));
			// Satelite should move left
			Assert::IsTrue(initialX > testSatellite.getPosition().getMetersX());

			// TEARDOWN
		}

		TEST_METHOD(GravityRight)
		{
			// SETUP - Place a Satelite to the left of Earth
			Simulator test = Simulator();

			Position initial = Position();
			double initialX = -GRAVITY_DISTANCE;
			double initialY = 0.0;
			initial.setMeters(initialX, initialY);

			Satellite testSatellite = Satellite(initial);
			test.addCollider(&testSatellite);

			// EXERCISE - Update Simulation
			test.update(GRAVITY_TEST_TIME);

			// VERIFY - Satelite should accelerate down
			// Make sure y didn't move (approximate for floating point)			
			Assert::IsTrue(closeEnough(initialY, testSatellite.getPosition().getMetersY(), tolerance));
			// Satelite should move right
			Assert::IsTrue(initialX < testSatellite.getPosition().getMetersX());


			// TEARDOWN
		}


		TEST_METHOD(CollisionHeadOn)
		{
			// SETUP			
			Simulator test = Simulator();
			// Two Satelites travelling towards eachother
			Satellite crashOne = Satellite();
			Satellite crashTwo = Satellite();

			// EXERCISE - Update position until they hit eachother
			double time = 100;
			test.update(time, false);

			// VERIFY - Satelites break apart upon collision
			Assert::IsTrue(crashOne.getCollided());
			Assert::IsTrue(crashTwo.getCollided());

			// TEARDOWN
		}

		TEST_METHOD(CollisionMeeting)
		{
			// SETUP
			Simulator test = Simulator();
			// Two Satelites travelling towards a single point,
			//  a collision where they glance off eachother
			Satellite crashOne = Satellite();
			Satellite crashTwo = Satellite();

			// EXERCISE - Update position until they hit eachother
			double time = 100;
			test.update(time, false);

			// VERIFY - Satelites break apart upon collision
			Assert::IsTrue(crashOne.getCollided());
			Assert::IsTrue(crashTwo.getCollided());

			// TEARDOWN
		}

		TEST_METHOD(CollisionTBone)
		{
			// SETUP
			Simulator test = Simulator();
			// A peaceful Satelite is crashed into by another Satelite
			Satellite crashOne = Satellite();
			Satellite crashTwo = Satellite();

			// EXERCISE - Update position until they hit eachother
			double time = 100;
			test.update(time, false);

			// VERIFY - Satelites break apart upon collision
			Assert::IsTrue(crashOne.getCollided());
			Assert::IsTrue(crashTwo.getCollided());

			// TEARDOWN
		}
		
		TEST_METHOD(GEO_Orbit)
		{
			// OPTIONAL, would need specific numbers
			// Place a Satelite in GEO orbit,
			// SETUP - Place a Satelite above the Earth

			const double GEO_TEST_HEIGHT = 35786000.0 + 6378000.0; // GEO orbit, items here should match Earth's rotation
			const double GEO_TEST_VEL_X = -3100.0;  // moving 3.1 km/s (to the left in this example)

			Simulator test = Simulator();
			Satellite orbitTest = Satellite(Position(0.0, GEO_TEST_HEIGHT), Velocity(GEO_TEST_VEL_X, 0.0));
			test.addCollider(&orbitTest);

			// EXERCISE - Do an orbit around the Earth
			double time = 600;
			test.update(time);

			// VERIFY - Correct position/velocity and didn't crash
			Assert::IsFalse(orbitTest.getCollided());

			Position expectedPos = Position(0.0, GEO_TEST_HEIGHT);
			// TODO: Make a closeEnough function for 2DValues
			Assert::IsTrue(closeEnough(expectedPos.getMetersX(), orbitTest.getPosition().getMetersX(), tolerance));
			Assert::IsTrue(closeEnough(expectedPos.getMetersY(), orbitTest.getPosition().getMetersY(), tolerance));

			// Velocity should also be about the same
			Assert::IsTrue(closeEnough(GEO_TEST_VEL_X, orbitTest.getVelocity().getMetersX(), tolerance));
			Assert::IsTrue(closeEnough(0, orbitTest.getVelocity().getMetersY(), tolerance));

			// TEARDOWN
		}

		TEST_METHOD(ConstantVelocity)
		{
			// SETUP
			Simulator test = Simulator();

			double initialPosX = 0.0;
			double initialPosY = 0.0;

			double initialVelX = 0.0;
			double initialVelY = 100.0;
			Satellite testSatellite = Satellite(Position(initialPosX, initialPosY), Velocity(initialVelX, initialVelY));

			// EXERCISE - Update position, without gravity
			double time = 100; // Time in seconds
			test.update(time, false);

			// VERIFY - Moved properly
			double expectedPosY = initialPosY + (initialVelY * time);
			Assert::IsTrue(closeEnough(expectedPosY, testSatellite.getPosition().getMetersY(), tolerance));
			// Velocity hasn't changed, nothing acting on it
			Assert::AreEqual(testSatellite.getVelocity().getMetersY(), initialVelY);

			// TEARDOWN		
		}
	};
}