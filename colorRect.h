#pragma once

#ifndef POSITION
#define POSITION
#include "position.h"
#endif

// colors ueed in the simulator
const int RGB_WHITE[] = { 255, 255, 255 };
const int RGB_LIGHT_GREY[] = { 196, 196, 196 };
const int RGB_GREY[] = { 128, 128, 128 };
const int RGB_DARK_GREY[] = { 64,   64,  64 };
const int RGB_DEEP_BLUE[] = { 64,   64, 156 };
const int RGB_BLUE[] = { 0,     0, 256 };
const int RGB_RED[] = { 255,   0,   0 };
const int RGB_GOLD[] = { 255, 255,   0 };
const int RGB_TAN[] = { 180, 150, 110 };
const int RGB_GREEN[] = { 0, 150,   0 };

/************************************************************
 * COLOR RECTANGLE
 * A structure used to conveniently specify a rectangle
 * of a certain color
 ************************************************************/

struct ColorRect
{
   // Offset
   //Position pos;

   // Size of the Rect
   int x0;
   int y0;
   int x1;
   int y1;
   int x2;
   int y2;
   int x3;
   int y3;

   // Color of the Rect
   const int* rgb;
};

