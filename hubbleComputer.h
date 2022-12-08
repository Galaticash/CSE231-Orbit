/***********************************************************************
 * Header File:
 *    Hubble Computer : A part in the orbital simulator that is created
 *    from a destroyed Hubble satellite.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    The Hubble computer has a radius of 7 and creates 2 fragments
 *    when destroyed.
 ************************************************************************/
#pragma once
#include "part.h"

/*********************************************
* HUBBLE COMPUTER
* A type of part in the orbit simulator.
*********************************************/
class HubbleComputer : public Part
{
public:
   HubbleComputer(Position pos = Position(), Velocity vel = Velocity(), Angle angle = Angle()) : Part(pos, vel, angle)
   {
      this->radius = 7; // Radius in pixels
      this->numFragments = 2;
   };


   /************************************************************************
    * DRAW Hubble Computer
    * Draw a the computer part of the hubble space telescope
    *  INPUT center    The position of the ship
    *        rotation  Which direction it is point
    *        offset    For pieces of the satellite, this is the relative position of the center
    *                  of rotation when it is connected to the main satellite
    *************************************************************************/
   /*
   void drawHubbleComputer(const Position& center, double rotation, const Position& offset)
   {
      ColorRect rects[] =
      {
         {-5,5,   0,5,  0,-3, -5,-3,  RGB_GREY},
         {-5,-5,  0,-5, 0,-3, -5,-3,  RGB_DARK_GREY},
         { 0,4,   3,4,  3,-2,  0,-2,  RGB_GREY},
         { 0,-4,  3,-4, 3,-2,  0,-2,  RGB_DARK_GREY},
      };

      for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
         glDrawRect(center, offset, rects[i], rotation);
   }*/
};