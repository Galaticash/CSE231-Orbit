/***************************************
* Satellite Test
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
	TEST_CLASS(SatelliteTest)
	{
	public:
		class testSimulator : public Simulator
		{
		public:
			testSimulator() {};
			void update() {
				// Update the position of each Object (all other objects are CollisionObjects
				for (vector<CollisionObject*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
				{
					CollisionObject* obj = *it;
					obj->update(TIME);
				}
			};
		};
		
		const double tolerance = 100.0;

		// utility funciton because floating point numbers are approximations
		bool closeEnough(double value, double test, double tolerence) const
		{
			double difference = value - test;
			return (difference >= -tolerence) && (difference <= tolerence);
		}

		/*
		class testSatellite : public Satellite
		{


		};*/

		
		TEST_METHOD(SatelliteTesting)
		{
			// The Satellites are correctly affected by gravity
			GravityDown();
			GravityUp();
			GravityLeft();
			GravityRight();

			// The Satellites collide with other objects
			// *Including Fragmnets and other Satelites
			CollisionHeadOn();
			CollisionMeeting();
			CollisionTBone();
		}

		TEST_METHOD(GravityDown)
		{
			// SETUP - Place a Satelite above the Earth
			testSimulator test = testSimulator();

			Position initial = Position();
			double initialX = 0.0;
			double initialY = 1000.0;
			initial.setMeters(initialX, initialY);

			Satellite testSatellite = Satellite(initial);
			test.addCollider(&testSatellite);

			// EXERCISE - Update Simulation
			test.update();

			// VERIFY - Satelite should accelerate down
			// Make sure x didn't move (approximate for floating point)			
			Assert::IsTrue(closeEnough(initialX, testSatellite.getPosition().getMetersX(), tolerance));
			// Satelite should move down
			Assert::IsTrue(testSatellite.getPosition().getMetersY() > testSatellite.getPosition().getMetersY());

			// TEARDOWN
		}

		TEST_METHOD(GravityUp)
		{
			// SETUP - Place a Satelite beneath the Earth
			testSimulator test = testSimulator();

			Position initial = Position();
			double initialX = 0.0;
			double initialY = 1000.0;
			initial.setMeters(initialX, initialY);

			Satellite testSatellite = Satellite(initial);
			test.addCollider(&testSatellite);

			// EXERCISE - Update Simulation
			test.update();

			// VERIFY - Satelite should accelerate down
			// Make sure x didn't move (approximate for floating point)			
			Assert::IsTrue(closeEnough(initialX, testSatellite.getPosition().getMetersX(), tolerance));
			// Satelite should move up
			Assert::IsTrue(testSatellite.getPosition().getMetersY() > testSatellite.getPosition().getMetersY());

			// TEARDOWN
		}

		TEST_METHOD(GravityLeft)
		{
			// SETUP -  Place a Satelite to the right of Earth
			testSimulator test = testSimulator();

			Position initial = Position();
			double initialX = 0.0;
			double initialY = 1000.0;
			initial.setMeters(initialX, initialY);

			Satellite testSatellite = Satellite(initial);
			test.addCollider(&testSatellite);

			// EXERCISE - Update Simulation
			test.update();

			// VERIFY - Satelite should accelerate down
			// Make sure y didn't move (approximate for floating point)			
			Assert::IsTrue(closeEnough(initialY, testSatellite.getPosition().getMetersY(), tolerance));
			// Satelite should move left
			Assert::IsTrue(testSatellite.getPosition().getMetersX() < testSatellite.getPosition().getMetersX());

			// TEARDOWN
		}

		TEST_METHOD(GravityRight)
		{
			// SETUP - Place a Satelite to the left of Earth
			testSimulator test = testSimulator();

			Position initial = Position();
			double initialX = 0.0;
			double initialY = 1000.0;
			initial.setMeters(initialX, initialY);

			Satellite testSatellite = Satellite(initial);
			test.addCollider(&testSatellite);

			// EXERCISE - Update Simulation
			test.update();

			// VERIFY - Satelite should accelerate down
			// Make sure y didn't move (approximate for floating point)			
			Assert::IsTrue(closeEnough(initialY, testSatellite.getPosition().getMetersY(), tolerance));
			// Satelite should move right
			Assert::IsTrue(testSatellite.getPosition().getMetersX() < testSatellite.getPosition().getMetersX());


			// TEARDOWN
		}


		TEST_METHOD(CollisionHeadOn)
		{
			// SETUP
			testSimulator testSim = testSimulator();
			
			// Two Satelites travelling towards eachother
			Satellite crashOne = Satellite();
			Satellite crashTwo = Satellite();
			testSim.addCollider(&crashOne);
			testSim.addCollider(&crashTwo);

			// EXERCISE - Update position until they hit eachother
			testSim.update();

			// VERIFY - Satelites break apart upon collision
			Assert::IsTrue(crashOne.collided(crashTwo));
			Assert::IsTrue(crashTwo.collided(crashOne));

			// TEARDOWN
		}

		TEST_METHOD(CollisionMeeting)
		{
			// SETUP
			// Two Satelites travelling towards a single point,
			//  a collision where they glance off eachother
			Satellite crashOne = Satellite();
			Satellite crashTwo = Satellite();


			// EXERCISE - Update position until they hit eachother


			// VERIFY - Satelites break apart upon collision
			Assert::IsTrue(crashOne.collided(crashTwo));
			Assert::IsTrue(crashTwo.collided(crashOne));

			// TEARDOWN

		}

		TEST_METHOD(CollisionTBone)
		{
			// SETUP
			// A peaceful Satelite is crashed into by another Satelite
			Satellite crashOne = Satellite();
			Satellite crashTwo = Satellite();

			// EXERCISE - Update position until they hit eachother


			// VERIFY - Satelites break apart upon collision
			Assert::IsTrue(crashOne.collided(crashTwo));
			Assert::IsTrue(crashTwo.collided(crashOne));

			// TEARDOWN

		}


		TEST_METHOD(GEO_Orbit)
		{
			// OPTIONAL, would need specific numbers
			// Place a Satelite in GEO orbit,
			// SETUP - Place a Satelite above the Earth


			// EXERCISE - Get Position/Acceleration


			// VERIFY - Satelite should accelerate down


			// TEARDOWN

		}

		TEST_METHOD(ConstantVelocity)
		{
			// SETUP
			// without gravity ?
			Satellite testSatellite = Satellite(Position(0.0, 0.0), Velocity(0, 100));

			// EXERCISE - Update position
			double time = 100; // Time in seconds
			testSatellite.update(time);

			// VERIFY - Is moving in Y direction
			testSatellite.getVelocity(); // Velocity hasn't changed, nothing acting on it


			// TEARDOWN		
		}

	};
}