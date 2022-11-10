/***************************************
* Collision Object Test
*
*
************************************/

#include "pch.h"
#include "CppUnitTest.h"
#include "../satellite.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CollisionObjectTest
{
	TEST_CLASS(CollisionObjectTest)
	{
	public:

		TEST_METHOD(TestCollisionObject)
		{
			GravityDown();
			GravityUp();
			GravityLeft();
			GravityRight();
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

		TEST_METHOD(GEO_Orbit)
		{
			// Place a Satelite in GEO orbit,
			// SETUP - Place a Satelite above the Earth


			// EXERCISE - Get Position/Acceleration


			// VERIFY - Satelite should accelerate down


			// TEARDOWN

		}


		TEST_METHOD(collision)
		{
			// SETUP - Place a Satelite above the Earth


			// EXERCISE - Get Position/Acceleration


			// VERIFY - Satelite should accelerate down


			// TEARDOWN

		}


	};
}