/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "pch.h"
#include "testRunner.h"
#include "testPosition.h"
#include "testSatellite.h"
#include "testBullet.h"

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
   cout << "Running Position tests.." << endl;
   // Runs Brother Helfrich's Position tests, 
   //  slightly modified since Position now inherits from 2DValue
   TestPosition().run();

   cout << "Running Satellite tests.." << endl;
   TestSatellite().run();

   cout << "Running Bullet tests.." << endl;
   TestBullet().run();

   cout << "All tests complete.";
}