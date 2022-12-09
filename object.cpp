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
