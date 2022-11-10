/***************************************
* Satelite Object Test
*
*
************************************/

#include "pch.h"
#include "CppUnitTest.h"
#include "../satellite.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SatelliteTest
{
	TEST_CLASS(SatelliteTest)
	{
	public:

		/*
		class testSatellite : public Satellite
		{


		};*/

		TEST_METHOD(Satellite)
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
			//testSatelite = Satelite();

			// EXERCISE - Get Position/Acceleration

			
			// VERIFY - Satelite should accelerate down


			// TEARDOWN
		}

		TEST_METHOD(GravityUp)
		{
			// SETUP - Place a Satelite beneath the Earth


			// EXERCISE - Get Position/Acceleration


			// VERIFY - Satelite should accelerate up


			// TEARDOWN
		}

		TEST_METHOD(GravityLeft)
		{
			// SETUP -  Place a Satelite to the right of Earth


			// EXERCISE - Get Position/Acceleration


			// VERIFY - Satelite should accelerate to the left


			// TEARDOWN

		}

		TEST_METHOD(GravityRight)
		{
			// SETUP - Place a Satelite to the left of Earth


			// EXERCISE - Get Position/Acceleration


			// VERIFY - Satelite should accelerate to the right


			// TEARDOWN

		}


		TEST_METHOD(CollisionHeadOn)
		{
			// SETUP
			// Two Satelites travelling towards eachother


			// EXERCISE - Update position until they hit eachother


			// VERIFY - Satelites break apart upon collision


			// TEARDOWN

		}

		TEST_METHOD(CollisionMeeting)
		{
			// SETUP
			// Two Satelites travelling towards a single point,
			//  a collision where they glance off eachother


			// EXERCISE - Update position until they hit eachother


			// VERIFY - Satelites break apart upon collision


			// TEARDOWN

		}

		TEST_METHOD(CollisionTBone)
		{
			// SETUP
			// A peaceful Satelite is crashed into by another Satelite


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

			// EXERCISE - Update position
		
			// VERIFY - goes in a staight line

			// TEARDOWN		
		}

	};
}