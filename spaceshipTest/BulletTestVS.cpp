/***************************************
* Bullet Test VS
* Test that a bullet will have the necessary info when
* it is created, and that it is deestroyed properly.
************************************/

#include "pch.h"
#include "CppUnitTest.h"
#include "../simulator.h"
//#include "../spaceship.h"
#include "BulletTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BulletTestVS
{

	void ShootMoving()
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

	void ShootStationary()
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

	void Expiration()
	{
		// SETUP - Have a lonely Spaceship
		Simulator test = Simulator();
		Bullet testBullet = Bullet();
		test.addCollider(&testBullet);


		// EXERCISE - Shoot a Bullet
		bool testExpiration = testBullet.isExpired();

		// VERIFY - Make sure the Bullet is deleted after the timer runs out
		Assert::IsTrue(testExpiration == true);
		//Assert::IsTrue(testBullet->lifetime >= 70);


		// TEARDOWN
	}

	void Collision()
	{
		// SETUP - Have a Spaceship facing another Collision Object to shoot at
		Simulator test = Simulator();
		Bullet testBullet = Bullet();
		test.addCollider(&testBullet);

		// EXERCISE - Shoot a Bullet
		bool testExpiration = testBullet.isExpired();

		// VERIFY - Make sure the Bullet is deleted EVEN IF its timer has not run out
		Assert::IsTrue(testExpiration == false);
		//Assert::IsTrue(testBullet->lifetime <= 69);
		// TEARDOWN
	}
}