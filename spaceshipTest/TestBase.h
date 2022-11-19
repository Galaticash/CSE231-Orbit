#pragma once
#include <iostream>

#ifndef C_ASSERT
#define C_ASSERT
#include <cassert>
#endif

using namespace std;

/*******************************
 * TEST
 * A type of class that performs tests for other classes
 * Sets up how other Tests are implemented (Position Test, Satellite Test, etc)
 ********************************/
class Test {
public:
   // A Method that will run all the Test's test
   virtual void run() {};

protected:
   // utility funciton because floating point numbers are approximations
   bool closeEnough(double value, double test, double tolerence) const
   {
      double difference = value - test;
      return (difference >= -tolerence) && (difference <= tolerence);
   }
};