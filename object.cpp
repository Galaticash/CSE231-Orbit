/***********************************************************************
 * Source File:
 *    Object : An Object in the orbital simulator. It has a position on
 *    the screen and can be drawn.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    An Object that can move around 2D space
 ************************************************************************/
#pragma once
#include "object.h"

/******************************************
* UPDATE
* Updates the position and velocity of the Object
* Takes the amount of time that has passed, and the gravity and radius of the Earth
********************************************/
void Object::update(double time, double gravity, double planetRadius)
{
   // Calculates the current angle and distance from the Earth (0, 0)
   double angleRad = gravityDirection(this->pos.getMetersX(), this->pos.getMetersY());
   double height = heightAbovePlanet(this->pos.getMetersX(), this->pos.getMetersY(), planetRadius);

   // Calculate the current acceleration
   double totalAcc = gravityEquation(height, planetRadius, gravity);

   Angle a;
   //a.setDegree(angleRad);
   a.setRadian(angleRad); // Treated as a Radian across the board
   TwoDValue acc;  
   acc.addMeters(totalAcc, a); // Works when using Radians (currenlty degrees)

   double vAcc = 
      //acc.getMetersY();
      verticalAcceleration(totalAcc, angleRad);
   double hAcc = 
      //acc.getMetersX();
      horizontalAcceleration(totalAcc, angleRad);

   // Update the current velocity with the current acceleration
   this->vel.setMetersX(velocityConstantAcceleration(this->vel.getMetersX(), hAcc, time));
   this->vel.setMetersY(velocityConstantAcceleration(this->vel.getMetersY(), vAcc, time));

   // Adjust the position given the current position, velocity, and acceleration
   double xGPS = distanceFormula(this->pos.getMetersX(), this->vel.getMetersX(), hAcc, time);
   double yGPS = distanceFormula(this->pos.getMetersY(), this->vel.getMetersY(), vAcc, time);

   // Update the current position
   this->pos.setMeters(xGPS, yGPS);
}
