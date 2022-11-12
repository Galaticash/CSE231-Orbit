
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
   // Use default constructor for any value not specified
   Object() : Object(Position(), Velocity(), Angle()) {};
   Object(Position pos) : Object(pos, Velocity(), Angle()) {};
   Object(Position pos, Velocity vel) : Object(pos, vel, Angle()) {};
   Object(Position pos, Velocity vel, Angle angle) { this->pos = pos; this->vel = vel; this->angle = angle; };

   // Getters
   Position getPosition()    const { return pos; }
   Velocity getVelocity()    const { return vel; }
   Angle getAngle()     const { return angle; }
   vector<Pixel>* getVisual() { return &visual; };

protected:
   Position pos;
   Velocity vel;
   Angle angle;
   vector <Pixel> visual;
};

