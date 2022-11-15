/************************************
* Bullet Test
* Header file for testing the bullet class.
*****************************************/
#pragma once
#include "TestBase.h"
#include "../bullet.h"

class BulletTest : public Test {
public:
   void run() {
      shootMoving();
   }
   void shootMoving();

};