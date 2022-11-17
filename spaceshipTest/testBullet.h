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

class stubDirectionUp : public dummyCollisionObject {
public:
   double getAngle() const { return 0.0; };
   Position getPosition() const { return Position(0.0, 0.0); }
   Velocity getVelocity() const { return Velocity(0.0, 0.0); }
};

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
      deleteExpire();
      deleteCollision();
   }
private:
   void shootStationary() const
   {
      // Setup
      stubDirectionUp ship;
      
      // Exercise
      Bullet test(ship.getPosition(), ship.getVelocity(), ship.getAngle());
      // Verify
      assert(test.pos.getMetersX() == 0.0);
   }  // Teardown
   
   void shootMoving() const 
   {
      // Setup
      stubMoveUp1000 ship;
      // Exercise
      Bullet test;
      // Verify
   }  // Teardown

   void deleteExpire() const
   {
      // Setup
      Bullet test;
      // Exercise
      // Verify
   }  // Teardown

   void deleteCollision() const
   {
      // Setup
      Bullet test;
      Bullet test2;
      // Exercise
      // Verify
   }  // Teardown
};