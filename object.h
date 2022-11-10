
#include "twoDValue.h"
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include "angle.h"
#include "pixel.h"
#include <vector>
#pragma once

using namespace std;

/*********************************************
 * Object
 * 
 *********************************************/
class Object
{
public:
   // Constructors
   Object();
   Object(TwoDValue pos, TwoDValue vel, Angle angle);

   // Getters
   TwoDValue getPosition()    const { return pos; }
   TwoDValue getVelocity()    const { return vel; }
   Angle getAngle()     const { return angle; }

private:
   TwoDValue pos;
   TwoDValue vel;
   Angle angle;
   vector <Pixel> visual;
};

