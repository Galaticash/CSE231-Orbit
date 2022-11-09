/***************************************
* Spaceship Test
*
*
************************************/

#include "pch.h"
#include "CppUnitTest.h"
#include "../spaceship.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace spaceshipTest
{
	TEST_CLASS(spaceshipTest)
	{
	public:
		
		TEST_METHOD(TestSpaceship)
		{
		}

		TEST_METHOD(TestSpaceshipRotateLeft)
		{
			// Setup
			Spaceship ship;
			// Execute
			// Verify
		}	// Teardown

		TEST_METHOD(TestSpaceshipRotateRight)
		{
		}

		TEST_METHOD(TestSpaceshipThrusterUp)
		{
		}

		/*
		*	Test gravity along the different axis'. 
		* No earth, no collision
		*/
		TEST_METHOD(TestSpaceshipGravityDown)
		{
		}

		TEST_METHOD(TestSpaceshipGravityUp)
		{
		}

		TEST_METHOD(TestSpaceshipGravityRight)
		{
		}

		TEST_METHOD(TestSpaceshipGravityLeft)
		{
		}

		// Test collision against another spaceship object.
		TEST_METHOD(TestSpaceshipCollision)
		{
		}
	};
}
