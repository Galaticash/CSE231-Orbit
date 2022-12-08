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

// TODO: Since including for random, should each Object have a "draw" method and just copy the methods in uiDraw?
// (Would make it more cohesive, Objects draw themselves instead of using the typeID)
#include "uiDraw.h" // To use random

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
   virtual void update(double time, double gravity, double planetRadius)
   {
      // ** QUESTION ** //
      // Would it be better to pass in Earth, or just the relevant attributes from Earth?
      // TODO: Assumes Planet is located at Position(0.0, 0.0) <-- could have that also be a parameter

      // Calculates the current angle and distance from the Earth (0, 0)
      double angle = gravityDirection(this->pos.getMetersX(), this->pos.getMetersY());
      double height = heightAbovePlanet(this->pos.getMetersX(), this->pos.getMetersY(), planetRadius);

      // Calculate the current acceleration
      double totalAcc = gravityEquation(height, planetRadius, gravity);
      double vAcc = verticalAcceleration(totalAcc, angle);
      double hAcc = horizontalAcceleration(totalAcc, angle);

      // Update the current velocity with the current acceleration
      this->vel.setMetersX(velocityConstantAcceleration(this->vel.getMetersX(), hAcc, time));
      this->vel.setMetersY(velocityConstantAcceleration(this->vel.getMetersY(), vAcc, time));
      
      // Adjust the position given the current position, velocity, and acceleration
      double xGPS = distanceFormula(this->pos.getMetersX(), this->vel.getMetersX(), hAcc, time);
      double yGPS = distanceFormula(this->pos.getMetersY(), this->vel.getMetersY(), vAcc, time);

      // Update the current position
      this->pos.setMeters(xGPS, yGPS);
   }

   // TODO: Each Object draws itself differently
   virtual void draw()
   {
      ColorRect rects[] =
      {
         {-7,7, 8,2, 8,-6, -7,-1,  RGB_GREY},
         {-6,6, 7,1, 7,-5, -6,0,   RGB_DEEP_BLUE}
      };

      for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
         glDrawRect(this->pos, 0, rects[i], this->rotationAngle.getDegree());
   }


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
   void addRotation(Angle newRotation) { rotationAngle += newRotation; };
   Angle getRotation()     const { return this->rotationAngle; }
   
protected:
   Position pos;  // The current Position of this Object
   Velocity vel;  // The current Velocity of this Object
   Angle rotationAngle; // The current rotation of this Object

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
    * h = distance between the surface of the earth and the object (meters)
    * x = horizontal position of object   (meters)
    * y = vertical position of object     (meters)
    * r = radius of earth                 (meters)
    *************************************************************************/
   double heightAbovePlanet(double x, double y, double radius) {
      double h = sqrt(x * x + y * y) - radius;
      return h;
   }

   /*************************************************************************
    * GRAVITY EQUATION
    * This calculates the total acceleration due to earth's gravity
    * Formula: g * ( r / ( r + h ) ) ^ 2 = gh
    * gh = magnitude of acceleration due to gravity at altitude h (m/s^2)
    * g  = gravity at sea level   (m/s^2)
    * r  = radius of earth        (meters)
    * h  = height above earth     (meters)
    *************************************************************************/
   double gravityEquation(double h, double radius, double gravity) {
      double gh = gravity * pow((radius / (radius + h)), 2);
      return gh;
   }

   /*************************************************************************
    * HORIZONTAL ACCELERATION
    * ddx = a * sin( angle )
    * ddx = horizontal component of acceleration      (m/s^2)
    * a = total acceleration                          (m/s^2)
    * angle = angle of the direction of acceleration  (0 degrees is up)
    *************************************************************************/
   double horizontalAcceleration(double a, double angle) {
      double ddx = a * sin(angle);
      return ddx;
   }

   /*************************************************************************
    * VERTICAL ACCELERATION
    * ddy = a * cos( angle )
    * ddy = vertical component of acceleration        (m/s^2)
    * a = total acceleration                          (m/s^2)
    * angle = angle of the direction of acceleration  (0 degrees is up)
    *************************************************************************/
   double verticalAcceleration(double a, double angle) {
      double ddy = a * cos(angle);
      return ddy;
   }

   /*************************************************************************
    * DISTANCE FORMULA
    * This formula is used for calculating the distance something travelled.
    * Can be used for both vertical and horizontal distance.
    * Formula: s = so + (v * t) + (.5 * a * t * t)
    *     ex. (x = xo + (dx * t) + (.5 * ddx * t * t))
    * s = distance            (meters)
    * so = initial distance   (meters)
    * v = velocity            (m/s)
    * t = time                (seconds)
    * a = acceleration        (m/s^2)
    *************************************************************************/
   double distanceFormula(double so, double v, double a, double t) {
      double s = so + (v * t) + (.5 * a * t * t);
      return s;
   }

   /*************************************************************************
    * POSITION CONSTANT VELOCITY
    * Compute the distance when given a constant velocity.
    * Can be used for both horizontal and vertical distance.
    * Formula: s = so + v * t
    *     ex. (x = xo + dx * t)
    * s  = distance           (meters)
    * so = initial position   (meters)
    * v  = velocity           (m/s)
    * t  = time               (seconds)
    *************************************************************************/
   double verticalConstantVelocity(double so, double v, double t) {
      double s = so + v * t;
      return s;
   }

   /*************************************************************************
    * VELOCITY CONSTANT ACCELERATION
    * Compute the velocity when given a constant acceleration.
    * Can be used for both horizontal and vertical velocity.
    * Formula: v = vo + a * t
    *    ex. (dx = dxo + ddx * t)
    * v = velocity            (m/s)
    * vo = initial velocity   (m/s)
    * a = acceleration        (m/s^2)
    * t = time                (seconds)
    *************************************************************************/
   double velocityConstantAcceleration(double vo, double a, double t) {
      double v = vo + a * t;
      return v;
   }
};