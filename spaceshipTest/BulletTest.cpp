/***************************************
* Bullet Test
*
*
************************************/

#include "pch.h"
#include "CppUnitTest.h"
#include "../simulator.h"
//#include "../spaceship.h"
#include "../bullet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BulletTest
{
	TEST_CLASS(BulletTest)
	{
	public:
		// Tolerance of floating point approximation
		const double tolerance = 100.0;

		// utility funciton because floating point numbers are approximations
		bool closeEnough(double value, double test, double tolerence) const
		{
			double difference = value - test;
			return (difference >= -tolerence) && (difference <= tolerence);
		}

		/*
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
		*/


		TEST_METHOD(ShootMoving)
		{
			// SETUP - Have a Spaceship with a constant velocity
			Simulator test = Simulator();

			double initialX = 0.0;
			double initialY = 0.0;
			Position initial = Position(initialX, initialY);

			double initialVelX = 0.0;
			double initialVelY = 100.0;
			Velocity initialVel = Velocity(initialVelX, initialVelY);

			double angle = 0.0;

			// EXERCISE - Shoot a Bullet
			test.createBullet(initial, initialVel, angle);

			// VERIFY - Bullet is moving at a constant velocity away from the Spacehip,
			//           9000m/s faster than the ship
			// bulletVel = 9100

			// TEARDOWN
		}

		TEST_METHOD(ShootStationary)
		{
			// SETUP - Have a stationary Spaceship
			Simulator test = Simulator();

			double initialX = 0.0;
			double initialY = 0.0;
			Position initial = Position(initialX, initialY);

			double initialVelX = 0.0;
			double initialVelY = 0.0;
			Velocity initialVel = Velocity(initialVelX, initialVelY);

			double angle = 0.0;

			// EXERCISE - Shoot a Bullet
			test.createBullet(initial, initialVel, angle);

			// VERIFY - Bullet is moving 9000m/s away from the Spaceship
			// bulletVel = 9000

			// TEARDOWN
		}

		TEST_METHOD(Expiration)
		{
			// SETUP - Have a lonely Spaceship
			Simulator test = Simulator();
			Bullet testBullet = Bullet();

			// EXERCISE - Shoot a Bullet
			bool testExpiration = testBullet.isExpired(); 

			// VERIFY - Make sure the Bullet is deleted after the timer runs out
			Assert::IsTrue(testExpiration == true);
			//Assert::IsTrue(testBullet->lifetime >= 70);

			
			// TEARDOWN
		}

		TEST_METHOD(Collision)
		{
			// SETUP - Have a Spaceship facing another Collision Object to shoot at
			Simulator test = Simulator();
			Bullet testBullet = Bullet();

			// EXERCISE - Shoot a Bullet
			bool testExpiration = testBullet.isExpired();

			// VERIFY - Make sure the Bullet is deleted EVEN IF its timer has not run out
			Assert::IsTrue(testExpiration == false);
			//Assert::IsTrue(testBullet->lifetime <= 69);
			// TEARDOWN
		}
	};
}