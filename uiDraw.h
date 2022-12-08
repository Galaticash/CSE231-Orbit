/***********************************************************************
 * Header File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#pragma once

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include <algorithm>  // used for min() and max()
#include "position.h" // Where things are drawn
using std::string;
using std::min;
using std::max;

#include <sstream>
#include "colorRect.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32


#define GL_SILENCE_DEPRECATION

/*************************************************************************
 * GRAPHICS STREAM
 * A graphics stream that behaves much like COUT except on a drawn screen
 *************************************************************************/
class ogstream : public std::ostringstream
{
public:
   ogstream(const Position& pt) : pt(pt) {}
   ~ogstream() { flush(); };
   void flush();

   void setPosition(const Position& pt) { flush(); this->pt = pt; }
   ogstream& operator = (const Position& pt)
   {
      setPosition(pt);
      return *this;
   }
private:
   Position pt;
};

void glDrawRect(const Position& center, const Position& offset,
   const ColorRect& rect, double rotation);

/************************************************************************
 * DRAW DIRECTION
 * Draws a line out at an angle from a center starting point
 *  INPUT center    The starting position of the line
 *        radius    The length of the line
 *        angle     The direction of the line
 *************************************************************************/
void drawDirection(const Position& center, const double radius, const Angle angle);

/************************************************************************
 * DRAW CIRCLE
 * Draws a circle
 *  INPUT center    The center of the circle
 *        radius    How large the cirle is
 *
 *  Modified from: github linusthe3rd's circles.cpp
 *  Has commented out code for a filled circle
 *************************************************************************/
void drawCircle(const Position& center, const double raidus);

/************************************************************************
 * DRAW LINE
 * Draws a Line
 *  INPUT one    The starting position of the line
 *        two    The ending position of the line
 *************************************************************************/
void drawLine(const Position& one, const Position& two);

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters 
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer/double
 ****************************************************************/
int    random(int    min, int    max);
double random(double min, double max);