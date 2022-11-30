/***********************************************************************
 * Header File:
 *    Test Two D Value : Tests the TwoDValue class
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Tests the basic functions of the TwoDValue class, along with 
 *    getting common angles.
 ************************************************************************/
#include "TestBase.h"
#include "../twoDValue.h"

class TestTwoDValue : public Test {
public:
   void run()
   {
      TwoDValue().setZoom(1000.0); /* 1km equals 1 pixel */

      // Copied from Position tests, 
      //  constructor and getter/setter tests
      copyConstructor();
      assignment();

      // Operator overloads
      addTwoD();        // Add two 2D values together
      subtractTwoD();   // Subtract a 2D value from another
      comparison();     // Compare two 2D values
      multiplyScale();  // Scale a 2D value

      // Test get total/hypotenuse
      getHypotenuse();

      // Test getAngle using special triangles
      getAngle45(); // 45 45 90
      getAngle30(); // 30 60 90
      getAngle60(); // 60 30 90
   }

private:
   // NOTE: Copied from Bro. Helfrich's Position tests
   void copyConstructor() const
   {  // SETUP
      TwoDValue twoD1;
      twoD1.x = 4000.0;
      twoD1.y = 2000.0;
      // EXERCISE
      TwoDValue twoD2(twoD1);
      // VERIFY
      assert(twoD1.getMetersX() == 4000.0);
      assert(twoD1.getMetersY() == 2000.0);
      assert(twoD2.getMetersX() == 4000.0);
      assert(twoD2.getMetersY() == 2000.0);
   }  // TEARDOWN
   void assignment() const
   {  // setup
      TwoDValue twoD1;
      twoD1.x = 4000.0;
      twoD1.y = 2000.0;
      // exercise
      TwoDValue twoD2 = twoD1;
      // verify
      assert(twoD1.getMetersX() == 4000.0);
      assert(twoD1.getMetersY() == 2000.0);
      assert(twoD2.getMetersX() == 4000.0);
      assert(twoD2.getMetersY() == 2000.0);
   }  // teardown

   // Addition and subtraction
   void addTwoD()
   {
      // SETUP
      TwoDValue initial;
      initial.x = 300.0;
      initial.y = 400.0;

      TwoDValue change;
      change.x = 100.0;
      change.y = 200.0;

      double expectedX = initial.x + change.x;
      double expectedY = initial.y + change.y;

      // EXERCISE
      initial += change;

      // VERIFY
      assert(closeEnough(expectedX, initial.x, .001));
      assert(closeEnough(expectedY, initial.y, .001));

      // TEARDOWN
   }
   void subtractTwoD()
   {
      // SETUP
      TwoDValue initial;
      initial.x = 300.0;
      initial.y = 400.0;

      TwoDValue change;
      change.x = 100.0;
      change.y = 200.0;

      double expectedX = initial.x - change.x;
      double expectedY = initial.y - change.y;

      // EXERCISE
      initial -= change;
      //initial -= change; // Show tests are working

      // VERIFY
      assert(closeEnough(expectedX, initial.x, .001));
      assert(closeEnough(expectedY, initial.y, .001));

      // TEARDOWN
   }

   void multiplyScale()
   {
      // SETUP
      TwoDValue initial;
      initial.x = 300.0;
      initial.y = 400.0;

      double scale = 2.0;

      double expectedX = initial.x * scale;
      double expectedY = initial.y * scale;

      // EXERCISE
      initial *= scale;

      // VERIFY
      assert(closeEnough(expectedX, initial.x, .001));
      assert(closeEnough(expectedY, initial.y, .001));

      // TEARDOWN
   }

   // Comparison
   void comparison()
   {
      // SETUP
      double valueX = 300.0;
      double valueY = 400.0;

      TwoDValue one;
      one.x = valueX;
      one.y = valueY;

      TwoDValue two;
      two.x = valueX;
      two.y = valueY;

      // EXERCISE
      bool sameVal = one == two;

      // VERIFY
      assert(sameVal);

      // TEARDOWN   
   }

   // Get Angle
   void getAngle30()
   {
      // SETUP
      TwoDValue test;

      double value = 400.0;

      // x to x sqrt(3) = 30 degree angle
      test.x = value * sqrt(3); // Adjacent
      test.y = value; // Opposite

      // EXERCISE - TwoDValue.getAngle()
      // Get the Angle between x and y
      Angle testA = test.getAngle();

      // VERIFY
      assert(closeEnough(30.0, testA.getDegree(), .001));

      // TEARDOWN
   }
   void getAngle45()
   {
      // SETUP
      TwoDValue test;

      double value = 400.0;

      // 1 to 1 = 45 degree angle
      test.x = value; // Adjacent
      test.y = value; // Opposite

      // EXERCISE - TwoDValue.getAngle()
      // Get the Angle between x and y
      Angle testA = test.getAngle();

      // VERIFY
      assert(closeEnough(45.0, testA.getDegree(), .001));

      // TEARDOWN
   }
   void getAngle60()
   {
      // SETUP
      TwoDValue test;

      double value = 400.0;

      // x to x sqrt(3) = 30 degree angle
      test.x = value; // Adjacent
      test.y = value * sqrt(3); // Opposite

      // EXERCISE - TwoDValue.getAngle()
      // Get the Angle between x and y
      Angle testA = test.getAngle();

      // VERIFY
      assert(closeEnough(60.0, testA.getDegree(), .001));

      // TEARDOWN
   }

   // Get Hypotenuse/Total
   void getHypotenuse()
   {
      // SETUP
      TwoDValue test;
      test.x = 400.0;
      test.y = 900.0;

      // Pythagoreon theorem
      double expected = sqrt(pow(test.x, 2) + pow(test.y, 2));

      // EXERCISE
      double h = test.getTotal();

      // VERIFY
      assert(closeEnough(expected, h, .001));

      // TEARDOWN
   }
};