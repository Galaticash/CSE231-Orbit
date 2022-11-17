/************************************
* Test Bullet
* Header file for testing the bullet class.
*****************************************/
#pragma once
#include "TestBase.h"
#include "../bullet.h"

class dummyCollisionObject : public CollisionObject {
public:
   dummyCollisionObject() : CollisionObject() {};

   virtual void update(double time, double gravity = 0.0, double planetRadius = 0.0) { assert(false); }

   virtual bool isHit(const CollisionObject& other) { assert(false); return false; };

   virtual void setCollided(bool c) { assert(false); }; // Simulator will check for collisions
   virtual bool getCollided() const { assert(false); return false; };

   // Normal Collision Objects will breakApart through deletion
   // And remove itself from the list
   virtual void breakApart() { assert(false); };
   virtual int getNumFragments() const { assert(false); return 0; };
   virtual double getRadius() const { assert(false);  return 0.0; };
};

// Stub for a ship that is pointed up, and goes nowhere.
class stubDirectionUp : public dummyCollisionObject {
public:
   double getAngle() const { return 0.0; };
   Position getPosition() const { return Position(0.0, 0.0); }
   Velocity getVelocity() const { return Velocity(0.0, 0.0); }
};

// Stub for a ship that is pointed up, and has a velocity of 10,000 m/s.
class stubMoveUp1000 : public dummyCollisionObject {
public:
   double getAngle() const { return 0.0; }
   Position getPosition() const { return Position(0.0, 0.0); }
   Velocity getVelocity() const { return Velocity(0.0, 1000.0); }
};

class TestBullet : public Test {
public:
   void run() {
      Position().setZoom(1000.0);
      shootStationary();
      shootMoving();
      expireTimer();
      expireCollision();
   }
private:
   void shootStationary() const
   {
      // Setup
      stubDirectionUp ship;
      Position spawnPos;
      spawnPos.addPixelsY(19.0);
      
      // Exercise
      Bullet test(ship.getPosition() + spawnPos, ship.getVelocity(), ship.getAngle());
      // Verify
      assert(closeEnough(test.pos.getMetersX(), 0.0, 0.1));
      assert(closeEnough(test.pos.getMetersY(), 19.0, 0.1));
      assert(closeEnough(test.angle, 0.0, 0.1));
      assert(closeEnough(test.vel.getMetersX(), 0.0, 0.1));
      assert(closeEnough(test.vel.getMetersY(), 9000.0, 1.0));
   }  // Teardown
   
   void shootMoving() const 
   {
      // Setup
      stubMoveUp1000 ship;
      Position spawnPos;
      spawnPos.addPixelsY(19.0);

      // Exercise
      Bullet test(ship.getPosition() + spawnPos, ship.getVelocity(), ship.getAngle());
      // Verify
      assert(closeEnough(test.pos.getMetersX(), 0.0, 0.1));
      assert(closeEnough(test.pos.getMetersY(), 19.0, 0.1));
      assert(closeEnough(test.angle, 0.0, 0.1));
      assert(closeEnough(test.vel.getMetersX(), 0.0, 0.1));
      assert(closeEnough(test.vel.getMetersY(), 10000.0, 1.0));
   }  // Teardown

   void expireTimer() const
   {
      // Setup
      Bullet test(Position(10.0, 10.0), Velocity(9000.0, 0.0), Angle());
      test.lifetime = 0;
      // Exercise
      bool expired = test.isExpired();
      // Verify
      assert(expired == true);
      assert(test.lifetime <= 0);
   }  // Teardown

   void expireCollision() const
   {
      // Setup
      Bullet test(Position(0.0, 10.0), Velocity(0.0, 0.0), Angle(0.0));
      Bullet test2(Position(0.0, 10.0), Velocity(0.0, 0.0), Angle(0.0));
      // Exercise
      bool expired = test.isExpired();
      // Verify
      assert(expired == true);
      assert(test.lifetime > 0);
   }  // Teardown
};