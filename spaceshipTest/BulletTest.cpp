/***************************************
* Bullet Test
*
*
************************************/

#include "pch.h"
#include "CppUnitTest.h"
#include "../spaceship.h"
#include "../bullet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BulletTest
{
	TEST_CLASS(BulletTest)
	{
	public:

		class DummyShip : public Spaceship
		{
			// Not controlled by user input
		};

		TEST_METHOD(Bullet)
		{
			// Place a bullet in front of a Dummy Spaceship
			ShootMoving();
			ShootStationary();

			// Make sure the Bullet disappears after time runs out
			Expiration();
			// But also make sure the timer doesn't affect collisions
			Collision();
		}


		TEST_METHOD(ShootMoving)
		{
			// SETUP - Have a Spaceship with a constant velocity

			// EXERCISE - Shoot a Bullet

			// VERIFY - Bullet is moving at a constant velocity away from the Spacehip,
			//           9000m/s faster than the ship

			// TEARDOWN
		}

		TEST_METHOD(ShootStationary)
		{
			// SETUP - Have a stationary Spaceship

			// EXERCISE - Shoot a Bullet

			// VERIFY - Bullet is moving 9000m/s away from the Spaceship

			// TEARDOWN
		}

		TEST_METHOD(Expiration)
		{
			// SETUP - Have a lonely Spaceship

			// EXERCISE - Shoot a Bullet

			// VERIFY - Make sure the Bullet is deleted after the timer runs out

			// TEARDOWN
		}

		TEST_METHOD(Collision)
		{
			// SETUP - Have a Spaceship facing another Collision Object to shoot at

			// EXERCISE - Shoot a Bullet

			// VERIFY - Make sure the Bullet is deleted EVEN IF its timer has not run out

			// TEARDOWN
		}

	};
}