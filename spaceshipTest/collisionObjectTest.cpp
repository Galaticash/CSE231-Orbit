/***************************************
* Collision Object Test
*
*
************************************/


#include "pch.h"
#include "CppUnitTest.h"
#include "../spaceship.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CollisionObjectTest
{
	TEST_CLASS(CollisionObjectTest)
	{
	public:

		TEST_METHOD(TestCollisionObject)
		{

		}

		TEST_METHOD(GravityDown)
		{
			// Place a Satelite above the Earth
			// Satelite should accelerate down


		}

		TEST_METHOD(GravityUp)
		{
			// Place a Satelite beneath the Earth
			// Satelite should accelerate up

		}

		TEST_METHOD(GravityLeft)
		{

			// Place a Satelite to the rigth of Earth
			// Satelite should accelerate to the left

		}

		TEST_METHOD(GravityRight)
		{
			// Place a Satelite to the left of Earth
			// Satelite should accelerate to the right

		}

		TEST_METHOD(GEO_Orbit)
		{
			// Place a Satelite in GEO orbit,

		}


	};
}