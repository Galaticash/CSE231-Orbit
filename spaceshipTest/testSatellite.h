#include "TestBase.h"
#include "../Satellite.h"
#include "../simulator.h"

class TestSatellite : public Test {

// All methods are public to share with VS test
// *Could friend VS test, but would have to look that up
public:
	void run()
   {
      // Set zoom to 1000.0 meters per pixel
      Position().setZoom(1000.0);

      // Testing updates to Position
      updatePos();

      // Testing number of parts broken into
      breakSubParts();

      // Testing explosion directions
      breakApartStatic();
      breakApartX();
      breakApartY();
   };

private:
   int randomSeed = 1;

   // Check that custom updates (no gravity) adjust the Position correctly
   void updatePos()
   {
      // SETUP
      Position initialPos = Position(300.0, 300.0);
      Velocity initialVel = Velocity(100.0, 0.0);

      Satellite test;
      // Setup Position
      test.pos.setMetersX(initialPos.getMetersX());
      test.pos.setMetersY(initialPos.getMetersY());
		
      // Setup Velocity
      test.vel.setMetersX(initialVel.getMetersX());
      test.vel.setMetersY(initialVel.getMetersY());

      // Constants used for update
      double time = 1;

      // EXERCISE
      test.update(time, 0.0, 0.0);

      // VERIFY
      double expectedPosX = initialPos.getMetersX() + (initialVel.getMetersX() * time);
      double expectedPosY = initialPos.getMetersY() + (initialVel.getMetersY() * time);
      assert(closeEnough(expectedPosX, test.pos.getMetersX(), .001));
      assert(closeEnough(expectedPosY, test.pos.getMetersY(), .001));

      // TEARDOWN	
   }

   class DummySimulator : public Simulator {
   public:
      DummySimulator() {}; // Doesn't create Ship or Earth

      // addCollider and removeCollider act as normal,
      //  used to tell if breakApart works

      // Only testing Satellite. No Stars, Ship, or Bullets
      void createStars() { assert(false);  };
      void createBullet(Position pos, Velocity vel, double angle) { assert(false); };
      void moveShip(double x, double y) { assert(false); };
   };

   class FakeSimulator : public DummySimulator {
   public:
      FakeSimulator() {};

      // Only update Collision Objects (Satellites, Parts, Fragments, Bullets)
      void update(double t = TIME, bool gravityOn = true)
      {
			/*
			vector<CollisionObject*> colliders = getCollisions();

			// For every object that collided,
			for (vector<CollisionObject*>::iterator it = colliders.begin(); it != colliders.end(); it++)
			{
				// Break the object apart, adding subParts to the Simulator's list of collisionObjects
				CollisionObject* obj = *it;
				obj->breakApart(this);
			}
			colliders.clear();
			*/

			/* Ignore stars */

         // Update the position of each CollisionObject
         for (CollisionObject* obj : collisionObjects)
         //for (vector<CollisionObject*>::iterator it = this->collisionObjects.begin(); it != this->collisionObjects.end(); it++)
         {
            // If gravity is turned off, passes 0 values
            double gravity = gravityOn ? GRAVITY : 0.0;
            double radius = gravityOn ? EARTH_RADIUS : 0.0;
            obj->update(t, gravity, radius);
         }
      };
		
      // Returns a list of Collision Object pointers
      list<CollisionObject*> getCollisionObjects() { return this->collisionObjects; };

      // To clear the current list of Collision Objects
      void clearObjects() { this->collisionObjects.clear(); this->collisionObjects = list<CollisionObject*>{}; };
   };

   // Check that the Satellite is breaking apart into the proper number of objects
   void breakSubParts() {
      // SETUP
      FakeSimulator fakeSim = FakeSimulator();
      fakeSim.clearObjects();

      // Can change inital Position if needed
      double initialX = 0.0;
      double initialY = 0.0;

      // Create a Satellite and get the number of Parts
      Satellite* testSatellite = new Satellite();
		
      // Set Position
      testSatellite->pos.setMeters(initialX, initialY);
		
      // Count up number of Parts and number of Fragments to break into
      vector<CollisionObject*> parts = { new Part(), new Part() };
      int expectedSubParts = parts.size() + testSatellite->numFragments;

      // Add the Satellite to the FakeSim and check that
      //  it is the only Object there
      fakeSim.addCollider(testSatellite);
      assert(fakeSim.getCollisionObjects().size() == 1);

      // EXERCISE - break apart the Satellite
      testSatellite->breakApart(&fakeSim, parts);

      // VERIFY
      // Satellite has broken into the correct number of SubParts
      assert(fakeSim.getCollisionObjects().size() == expectedSubParts);
		
      // TEARDOWN	
   }

   // Check that the Satellite's subParts are set with the correct directions/velocities when the Satellite is not moving
   void breakApartStatic() {
      // SETUP 
      FakeSimulator fakeSim = FakeSimulator();
      fakeSim.clearObjects();

      // Can change inital Position if needed
      Position initialP = Position(0.0, 0.0);
      Velocity initialV = Velocity(0.0, 0.0);

      // Create a Satellite and get the number of Parts
      Satellite* testSatellite = new Satellite();

      // Set Position
      testSatellite->pos.setMeters(initialP.getMetersX(), initialP.getMetersY());
      // Set Velocity
      testSatellite->vel.setMeters(initialV.getMetersX(), initialV.getMetersY());

      // Set collection of Parts
      vector<CollisionObject*> parts = { new Part(), new Part() };
      int expectedSubParts = parts.size() + testSatellite->numFragments;

      // Add the Satellite to the FakeSim and check that
      //  it is the only Object there
      fakeSim.addCollider(testSatellite);
      assert(fakeSim.getCollisionObjects().size() == 1);
		

      srand(randomSeed); // Seed the random

      // IMPORTANT: Ensure seeded random is in the same place
      // random() is called when a Fragment is created (both for fragment lifetime and initial rotation)
      for (int i = 0; i < testSatellite->numFragments; i++)
         Fragment();

      // Find the expected part directions and positions
      vector<Velocity> expectedDirections = testSatellite->getSubPartVel(expectedSubParts);
      vector<Position> expectedPositions = testSatellite->getSubPartPos(expectedDirections);

      srand(randomSeed); // Seed the random
		
      // EXERCISE - break apart the Satellite
      testSatellite->breakApart(&fakeSim, parts);

      // VERIFY
      list<CollisionObject*> collisionObjects = fakeSim.getCollisionObjects();
      assert(collisionObjects.size() == expectedSubParts);
		
      // Check that all objects are travelling in different directions (Satellite's velocity added)
      vector<Position>::iterator pos = expectedPositions.begin();
      vector<Velocity>::iterator dir = expectedDirections.begin();
		
      for (CollisionObject* testing : collisionObjects)
      //for (vector<CollisionObject*>::iterator obj = collisionObjects.begin(); obj != collisionObjects.end(); obj++)
      {
         // Iterators changed into their classes
         //CollisionObject* testing = (*obj);
         Position expectedPos = *pos;
         Velocity expectedVel = *dir;

         // Check Position
         assert(closeEnough(testing->pos.getMetersX(), expectedPos.getMetersX(), .001));
         assert(closeEnough(testing->pos.getMetersY(), expectedPos.getMetersY(), .001));

         // Check Velocity/Direction
         assert(closeEnough(testing->vel.getMetersX(), expectedVel.getMetersX(), .001));
         assert(closeEnough(testing->vel.getMetersY(), expectedVel.getMetersY(), .001));

         // Move to next object
         pos++;
         dir++;
      }		
		
      // TEARDOWN
   }

   // Check that the Satellite's subParts are set with the correct directions/velocities when the Satellite is moving in the X direction
   void breakApartX() {
      // SETUP 
      FakeSimulator fakeSim = FakeSimulator();
      fakeSim.clearObjects();

      // Can change inital Position if needed
      Position initialP = Position(0.0, 0.0);
      Velocity initialV = Velocity(1000.0, 0.0);

      // Create a Satellite and get the number of Parts
      Satellite* testSatellite = new Satellite();

      // Set Position
      testSatellite->pos.setMeters(initialP.getMetersX(), initialP.getMetersY());
      // Set Velocity
      testSatellite->vel.setMeters(initialV.getMetersX(), initialV.getMetersY());
		
      // Set collection of Parts
      vector<CollisionObject*> parts = { new Part(), new Part() };
      int expectedSubParts = parts.size() + testSatellite->numFragments;
      //testSatellite->parts.size() + testSatellite->numFragments;

      srand(randomSeed); // Seed the random

      // IMPORTANT: Ensure seeded random is in the same place
      // random() is called when a Fragment is created (both for fragment lifetime and initial rotation)
      for (int i = 0; i < testSatellite->numFragments; i++)
         Fragment();

      // Find the expected part directions and positions
      vector<Velocity> expectedDirections = testSatellite->getSubPartVel(expectedSubParts);
      vector<Position> expectedPositions = testSatellite->getSubPartPos(expectedDirections);

      srand(randomSeed); // Seed the random

      // EXERCISE
      testSatellite->breakApart(&fakeSim, parts);

      // VERIFY
      list<CollisionObject*> collisionObjects = fakeSim.getCollisionObjects();
      assert(collisionObjects.size() == expectedSubParts);

      // Check that all objects are travelling in different directions (Satellite's velocity added)
      vector<Position>::iterator pos = expectedPositions.begin();
      vector<Velocity>::iterator dir = expectedDirections.begin();
		
      for (CollisionObject* testingX : collisionObjects)
      //for (vector<CollisionObject*>::iterator obj = collisionObjects.begin(); obj != collisionObjects.end(); obj++)
      {
         // Iterators changed into their classes
         //CollisionObject* testingX = (*obj);
         Position expectedPos = *pos;
         Velocity expectedVel = *dir;
			
         // Check Position
         assert(closeEnough(testingX->pos.getMetersX(), expectedPos.getMetersX(), .001));
         assert(closeEnough(testingX->pos.getMetersY(), expectedPos.getMetersY(), .001));
			
         // Check Velocity/Direction
         assert(closeEnough(testingX->vel.getMetersX(), expectedVel.getMetersX(), .001));
         assert(closeEnough(testingX->vel.getMetersY(), expectedVel.getMetersY(), .001));

         // Move to next object
         pos++;
         dir++;
      }		

      // TEARDOWN
   }

   // Check that the Satellite's subParts are set with the correct directions/velocities when the Satellite is moving in the Y direction
   void breakApartY() {
      // SETUP 
      FakeSimulator fakeSim = FakeSimulator();
      fakeSim.clearObjects(); // Double check that there are no additional objects

      // Can change inital Position if needed
      Position initialP = Position(0.0, 0.0);
      Velocity initialV = Velocity(0.0, 1000.0);

      // Create a Satellite and get the number of Parts
      Satellite* testSatellite = new Satellite();

      // Set Position
      testSatellite->pos.setMeters(initialP.getMetersX(), initialP.getMetersY());
      // Set Velocity
      testSatellite->vel.setMeters(initialV.getMetersX(), initialV.getMetersY());
		
      // Set collection of Parts
      vector<CollisionObject*> parts = { new Part(), new Part() };
      int expectedSubParts = parts.size() + testSatellite->numFragments;

      srand(randomSeed); // Seed the random

      // IMPORTANT: Ensure seeded random is in the same place
      // random() is called when a Fragment is created (both for fragment lifetime and initial rotation)
      for (int i = 0; i < testSatellite->numFragments; i++)
         Fragment();

      // Find the expected part directions and positions
      vector<Velocity> expectedDirections = testSatellite->getSubPartVel(expectedSubParts);
      vector<Position> expectedPositions = testSatellite->getSubPartPos(expectedDirections);

      srand(randomSeed); // Seed the random

      // EXERCISE - Break apart the Satellite
      testSatellite->breakApart(&fakeSim, parts);

      // VERIFY
      list<CollisionObject*> collisionObjects = fakeSim.getCollisionObjects();
      assert(collisionObjects.size() == expectedSubParts);

      // Check that all objects are travelling in different directions (Satellite's velocity added)
      vector<Position>::iterator pos = expectedPositions.begin();
      vector<Velocity>::iterator dir = expectedDirections.begin();

      for (CollisionObject* testingY : collisionObjects)
      //for (vector<CollisionObject*>::iterator obj = collisionObjects.begin(); obj != collisionObjects.end(); obj++)
      {
         //CollisionObject* testingY = (*obj);
         Position expectedPos = *pos;
         Velocity expectedVel = *dir;

         // Check Position
         assert(closeEnough(testingY->pos.getMetersX(), expectedPos.getMetersX(), .001));
         assert(closeEnough(testingY->pos.getMetersY(), expectedPos.getMetersY(), .001));

         // Check Velocity/Direction
         assert(closeEnough(testingY->vel.getMetersX(), expectedVel.getMetersX(), .001));
         assert(closeEnough(testingY->vel.getMetersY(), expectedVel.getMetersY(), .001));

         // Move to next object
         pos++;
         dir++;
      }

      // TEARDOWN
   }
};