/***********************************************************************
 * Header File:
 *    Object : An Object in the orbital simulator. It has a position on
 *    the screen and can be drawn.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    An Object that can move around 2D space
 ************************************************************************/
#pragma once
#include "position.h" // The (x, y) position on the screen
#include "velocity.h" // The (x, y) direction the Object is travelling
#include "angle.h"    // The Object's angle of rotation

#ifndef C_ASSERT
#define C_ASSERT
#include <cassert>
#endif  // To make assertions

#include "uiDraw.h" // To use random (TODO: Put in a separate file?)

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
class TestSatellite;

/*********************************************
 * Object
 * An object in the orbital simulator.
 *********************************************/
class Object
{
public:
   friend TestSatellite; // For test cases

   // Constructor taking an initial Position, Velocity, and Angle
   // If none given, uses default constructors
   Object(Position pos = Position(), Velocity vel = Velocity(), Angle rotation = Angle()) 
   { 
      this->pos = pos;
      this->vel = vel;
      this->rotationAngle = rotation;
   };
   
   /******************************************
   * UPDATE
   * Updates the position and velocity of the Object
   * Takes the amount of time that has passed, and the gravity and radius of the Earth
   ********************************************/
   virtual void update(double time, double gravity, double planetRadius);

   // Position Getters and Setters
   void setPosition(Position newPos) { this->pos = newPos; };
   Position getPosition()    const { return pos; }

   // Velocity Getters and Setters
   void setVelocity(Velocity newVel) { this->vel = newVel; };
   Velocity getVelocity()    const { return vel; }

   // Add a Velocity to this Object
   void addVelocity(Velocity v) { this->vel += v; };
   void addVelocity(double velX, double velY) { this->vel.addMetersX(velX); this->vel.addMetersY(velY); };
   
   // Add Rotation and get Rotation
   void addRotation(Angle change) { rotationAngle += change; };
   Angle getRotation()     const { return this->rotationAngle; }
   
protected:
   Position pos;  // The current Position of this Object
   Velocity vel;  // The current Velocity of this Object
   Angle rotationAngle; // The current rotation of this Object

   // PHYSICS FUNCTIONS

   /*************************************************************************
    * GRAVITY DIRECTION
    * Calculates the angle at which an object is pulled by gravity.
    * Assumes Earth is located at (0, 0)
    * Fromula: d = atan( xe - xs, ye - ys )
    * d = direction of the pull of gravity      (radians)
    * xe = horizontal position of the center of the earth : 0m
    * ye = vertical position of the center of the earth : 0m
    * xs = horizontal position of the satellite (meters)
    * ys = vertical position of the satellite   (meters)
    *************************************************************************/
   double gravityDirection(double xs, double ys) {
      double d = atan2(xs, ys);
      return d;
   }

   /*************************************************************************
    * HEIGHT ABOVE EARTH
    * Finds the height above the earth an object is.
    * Assumes Earth is located at (0, 0)
    * Formula: h = sqrt(x * x + y * y) - r
    * Returns the distance between the surface of the earth and the object (meters)
    * x = horizontal position of object   (meters)
    * y = vertical position of object     (meters)
    * r = radius of earth                 (meters)
    *************************************************************************/
   double heightAbovePlanet(const double x, const double y, const double r) {
      return sqrt(x * x + y * y) - r;
   }

   /*************************************************************************
    * GRAVITY EQUATION
    * This calculates the total acceleration due to earth's gravity
    * Formula: g * ( r / ( r + h ) ) ^ 2 = gh
    * Returns the magnitude of acceleration due to gravity at altitude h (m/s^2)
    * g  = gravity at sea level   (m/s^2)
    * r  = radius of earth        (meters)
    * h  = height above earth     (meters)
    *************************************************************************/
   double gravityEquation(const double h, const double r, const double g) {
      return g * pow((r / (r + h)), 2);
   }

   /*************************************************************************
    * HORIZONTAL ACCELERATION
    * ddx = a * sin( angle )
    * Returns the horizontal component of acceleration      (m/s^2)
    * acc = total acceleration                          (m/s^2)
    * angle = angle of the direction of acceleration  (0 degrees is up)
    *************************************************************************/
   double horizontalAcceleration(const double acc, const double angle) {
      return acc * sin(angle);
   }

   /*************************************************************************
    * VERTICAL ACCELERATION
    * ddy = a * cos( angle )
    * Returns the vertical component of acceleration        (m/s^2)
    * acc = total acceleration                          (m/s^2)
    * angle = angle of the direction of acceleration  (0 degrees is up)
    *************************************************************************/
   double verticalAcceleration(const double acc, const double angle) {
      return acc * cos(angle);
   }

   /*************************************************************************
    * DISTANCE FORMULA
    * This formula is used for calculating the distance something travelled.
    * Can be used for both vertical and horizontal distance.
    * Formula: s = so + (v * t) + (.5 * a * t * t)
    *     ex. (x = xo + (dx * t) + (.5 * ddx * t * t))
    * Returns the new distance   (meters)
    * so = initial distance   (meters)
    * v = velocity            (m/s)
    * t = time                (seconds)
    * a = acceleration        (m/s^2)
    *************************************************************************/
   double distanceFormula(const double so, const double v, const double a, const double t) {
      return so + (v * t) + (.5 * a * t * t);
   }

   /*************************************************************************
    * POSITION CONSTANT VELOCITY
    * Compute the distance when given a constant velocity.
    * Can be used for both horizontal and vertical distance.
    * Formula: s = so + v * t
    *     ex. (x = xo + dx * t)
    * Returns the new distance   (meters)
    * so = initial position   (meters)
    * v  = velocity           (m/s)
    * t  = time               (seconds)
    *************************************************************************/
   double verticalConstantVelocity(const double so, const double v, const double t) {
      return so + v * t;
   }

   /*************************************************************************
    * VELOCITY CONSTANT ACCELERATION
    * Compute the velocity when given a constant acceleration.
    * Can be used for both horizontal and vertical velocity.
    * Formula: v = vo + a * t
    *    ex. (dx = dxo + ddx * t)
    * Returns the new velocity   (m/s)
    * vo = initial velocity   (m/s)
    * a = acceleration        (m/s^2)
    * t = time                (seconds)
    *************************************************************************/
   double velocityConstantAcceleration(const double vo, const double a, const double t) {
      return vo + a * t;
   }
};