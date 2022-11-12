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
		};

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
			initial.setMeters(0.0, 1000);

			Satellite testSatellite = Satellite(initial);
			test.addCollider(&testSatellite);

			// EXERCISE - Update Simulation
			test.update();

			// VERIFY - Satelite should accelerate down
			testSatellite.getPosition(); // Turn into assert, Y is down
			// Make sure x didn't move


			// TEARDOWN
		}

		TEST_METHOD(GravityUp)
		{
			// SETUP - Place a Satelite beneath the Earth
			Satellite testSatellite = Satellite();

			// EXERCISE - Update Position


			// VERIFY - Satelite should accelerate up


			// TEARDOWN
		}

		TEST_METHOD(GravityLeft)
		{
			// SETUP -  Place a Satelite to the right of Earth
			Satellite testSatellite = Satellite();

			// EXERCISE - Update Position


			// VERIFY - Satelite should accelerate to the left


			// TEARDOWN

		}

		TEST_METHOD(GravityRight)
		{
			// SETUP - Place a Satelite to the left of Earth
			Satellite testSatellite = Satellite();

			// EXERCISE - Update Position


			// VERIFY - Satelite should accelerate to the right


			// TEARDOWN

		}


		TEST_METHOD(CollisionHeadOn)
		{
			// SETUP
			// Two Satelites travelling towards eachother
			Satellite crashOne = Satellite();
			Satellite crashTwo = Satellite();


			// EXERCISE - Update position until they hit eachother


			// VERIFY - Satelites break apart upon collision
			crashOne.collided(crashTwo);
			crashTwo.collided(crashOne);

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


			// TEARDOWN

		}


		TEST_METHOD(GEO_Orbit)
		{
			// OPTIONAL, no real way to test
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
			Satellite testSatellite = Satellite();

			// EXERCISE - Update position

			// VERIFY - goes in a staight line

			// TEARDOWN		
		}

	};
}