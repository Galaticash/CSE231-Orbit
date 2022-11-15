/***********************************************************************
 * Header File:
 *    Test Position : Test the Position class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the unit tests for Position
 ************************************************************************/

#pragma once
#include "TestBase.h"
#include "../position.h"

/*******************************
 * TEST Position
 * A friend class for Position which contains the Position unit tests
 ********************************/
class TestPosition : class Test
{
public:
   void run()
   {
      Position().setZoom(1000.0 /* 1km equals 1 pixel */);
      defaultConstructor();
      nonDefaultConstructor();
      copyConstructor();
      assignment();
 
      setPixels();
      setMeters();
      
      addPixels();
      addMeters();
   }
   
private:
   void defaultConstructor() const
   {  // setup
      // exercise
      Position pos;
      // verify
      assert(pos.getMetersX() == 0.0);
      assert(pos.getMetersY() == 0.0);
   }  // teardown

   void nonDefaultConstructor() const
   {  // setup
      // exercise
      Position pos(3000.0, 9000.0);
      // verify
      assert(pos.getMetersX() == 3000.0);
      assert(pos.getMetersY() == 9000.0);
   }  // teardown

   void copyConstructor() const
   {  // setup
      Position pos1;
      pos1.x = 4000.0;
      pos1.y = 2000.0;
      // exercise
      Position pos2(pos1);
      // verify
      assert(pos1.getMetersX() == 4000.0);
      assert(pos1.getMetersY() == 2000.0);
      assert(pos2.getMetersX() == 4000.0);
      assert(pos2.getMetersY() == 2000.0);
   }  // teardown

   void assignment() const
   {  // setup
      Position pos1;
      pos1.x = 4000.0;
      pos1.y = 2000.0;
      // exercise
      Position pos2 = pos1;
      // verify
      assert(pos1.getMetersX() == 4000.0);
      assert(pos1.getMetersY() == 2000.0);
      assert(pos2.getMetersX() == 4000.0);
      assert(pos2.getMetersY() == 2000.0);
   }  // teardown
   
   void setMeters() const
   {  // setup
      Position pos;
      pos.x = 0.0;
      pos.y = 0.0;
      // exercise
      pos.setMetersX(5000.0);
      pos.setMetersY(3000.0);
      // verify
      assert(pos.getMetersX() == 5000.0);
      assert(pos.getMetersY() == 3000.0);
   }  // teardown
 
   void setPixels() const
   {  // setup
      Position pos;
      pos.x = 0.0;
      pos.y = 0.0;
      // exercise
      pos.setPixelsX(6.0);
      pos.setPixelsY(12.0);
      // verify
      assert(pos.getMetersX() == 6000.0);
      assert(pos.getMetersY() == 12000.0);
   }  // teardown
   
   void addMeters() const
   {  // setup
      Position pos;
      pos.x = 800.0;
      pos.y = 1600.0;
      // exercise
      pos.addMetersX(-400.0);
      pos.addMetersY(800.0);
      // verify
      assert(pos.getMetersX() == 400.0);
      assert(pos.getMetersY() == 2400.0);
   }  // teardown
   
   void addPixels() const
   {  // setup
      Position pos;
      pos.x = 2000.0;
      pos.y = 4000.0;
      // exercise
      pos.addPixelsX(2);
      pos.addPixelsY(3);
      // verify
      assert(pos.getMetersX() == 4000.0);
      assert(pos.getMetersY() == 7000.0);
   }  // teardown

};
