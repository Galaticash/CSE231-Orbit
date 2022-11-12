#pragma once
/*********************************************
 * Object
 *
 *********************************************/

#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include "angle.h"
#include "colorRect.h"
#include <vector>

using namespace std;

/* TODO: Consts here or in Simulator? */

const double GRAVITY = -9.8067;           // Gravity constant in m/s^2
const double EARTH_RADIUS = 6378000.0;    // meters


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
   double getAngle()     const { return 0.0; }
      //return angle; } // Have angle.getRadians and angle.getDegrees
   vector<ColorRect> getVisual() const { return visual; };

   void update(double time)
   {
      // TODO: Pass time or Global Const?
      // *TODO: Check isCollided here? If !isCollided, else destroy?

      // Calculates the current angle and distance from the Earth (0, 0)
      double angle = gravityDirection(this->pos.getMetersX(), this->pos.getMetersY());
      double height = heightAboveEarth(this->pos.getMetersX(), this->pos.getMetersY());

      // Calculate the current acceleration
      double totalAcc = gravityEquation(height);
      double vAcc = verticalAcceleration(totalAcc, angle);
      double hAcc = horizontalAcceleration(totalAcc, angle);

      // Update the current velocity with the current acceleration
      this->vel.setMetersHorizontal(velocityConstantAcceleration(this->vel.getMetersHorizontal(), hAcc, time));
      this->vel.setMetersVertical(velocityConstantAcceleration(this->vel.getMetersVertical(), vAcc, time));

      // Adjust the position given the current position, velocity, and acceleration
      double xGPS = distanceFormula(this->pos.getMetersX(), this->vel.getMetersHorizontal(), hAcc, time);
      double yGPS = distanceFormula(this->pos.getMetersY(), this->vel.getMetersVertical(), vAcc, time);

      // Update the current position
      this->pos = Position(xGPS, yGPS);
   }

   /*************************************************************************
    * GRAVITY DIRECTION
    * Calculates the angle at which an object is pulled by gravity.
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
    * Formula: h = sqrt(x * x + y * y) - r
    * h = distance between the surface of the earth and the object (meters)
    * x = horizontal position of object   (meters)
    * y = vertical position of object     (meters)
    * r = radius of earth                 (meters)
    *************************************************************************/
   double heightAboveEarth(double x, double y) {
      double h = sqrt(x * x + y * y) - EARTH_RADIUS;
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
   double gravityEquation(double h) {
      // TODO: Figure out if it is better to repeat this equation or to use the square function
      double gh = GRAVITY * pow((EARTH_RADIUS / (EARTH_RADIUS + h)), 2);
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

protected:
   Position pos;
   Velocity vel;
   Angle angle;
   vector <ColorRect> visual;
};

