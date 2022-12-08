/***********************************************************************
 * Source File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock

#include "uiDraw.h"

using namespace std;

const double PI = 3.1415926; // Pi, to calculate circles

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  origin   The center point we will rotate around
 *           x,y      Offset from center that we will be rotating, in pixels
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
Position rotate(const Position& origin, double x, double y, double rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(rotation);
   double sinA = sin(rotation);

   // start with our original point
   Position ptReturn(origin);

   // find the new values
   ptReturn.addPixelsX(x * cosA + y * sinA);
   ptReturn.addPixelsY(y * cosA - x * sinA);

   return ptReturn;
}

/*************************************************************************
 * GL RESET COLOR
 * Just a more convenient way to reset the color
 *************************************************************************/
inline void glResetColor()
{
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
}   

/************************************************************************
* GL COLOR
* Set the color on the board
*   INPUT  rgb  RGB color in integers (0...255)
*************************************************************************/
void glColor(const int* rgb)
{
   glColor3f((GLfloat)(rgb[0] / 256.0),
             (GLfloat)(rgb[1] / 256.0),
             (GLfloat)(rgb[2] / 256.0));
}

/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position & point)
{
   glVertex2f((GLfloat)point.getPixelsX(), (GLfloat)point.getPixelsY());
}

/*************************************************************************
 * GL DRAW RECT
 * Draw a colored rectangle
 *************************************************************************/
void glDrawRect(const Position & center, const Position & offset,
                const ColorRect & rect, double rotation)
{
   glBegin(GL_QUADS);
   glColor(rect.rgb);
   glVertexPoint(rotate(center,
                        rect.x0 + offset.getPixelsX(),
                        rect.y0 + offset.getPixelsY(),
                        rotation));
   glVertexPoint(rotate(center,
                        rect.x1 + offset.getPixelsX(),
                        rect.y1 + offset.getPixelsY(),
                        rotation));
   glVertexPoint(rotate(center,
                        rect.x2 + offset.getPixelsX(),
                        rect.y2 + offset.getPixelsY(),
                        rotation));
   glVertexPoint(rotate(center,
                        rect.x3 + offset.getPixelsX(),
                        rect.y3 + offset.getPixelsY(),
                        rotation));
   glEnd();
}

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void drawText(const Position& topLeft, const char* text)
{
   void* pFont = GLUT_BITMAP_HELVETICA_12;  // also try _18

   // prepare to draw the text from the top-left corner
   glRasterPos2f((GLfloat)topLeft.getPixelsX(),
                 (GLfloat)topLeft.getPixelsY());

   // loop through the text
   for (const char* p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}

/*************************************************************************
 * DISPLAY the results on the screen
 *************************************************************************/
void ogstream :: flush()
{
   string sOut;
   string sIn = str();

   // copy everything but the newlines
   for (string::iterator it = sIn.begin(); it != sIn.end(); ++it)
      // newline triggers an buffer flush and a move down
      if (*it == '\n')
      {
         drawText(pt, sOut.c_str());
         sOut.clear();
         pt.addPixelsY(-18);
      }
      // othewise append
      else
         sOut += *it;

   // put the text on the screen
   if (!sOut.empty())
   {
      drawText(pt, sOut.c_str());
      pt.addPixelsY(-18);
   }
   
   // reset the buffer
   str("");
}

/************************************************************************
 * DRAW DIRECTION
 * Draws a line out at an angle from a center starting point
 *  INPUT center    The starting position of the line
 *        radius    The length of the line
 *        angle     The direction of the line
 *************************************************************************/
void drawDirection(const Position& center, const double radius, const Angle angle)
{
   Position outer = Position(center.getMetersX(), center.getMetersY());
   outer.addPixels(radius * 2, angle);
   drawLine(center, outer);
};

/************************************************************************
 * DRAW LINE
 * Draws a Line
 *  INPUT one    The starting position of the line
 *        two    The ending position of the line
 *************************************************************************/
void drawLine(const Position& one, const Position& two)
{
    // Draw in gold
    glColor3f(RGB_GOLD[0], RGB_GOLD[1], RGB_GOLD[2]);

    glBegin(GL_LINES);

    glVertex2f(one.getPixelsX(), one.getPixelsY());
    glVertex2f(two.getPixelsX(), two.getPixelsY());

    glEnd();
}

/************************************************************************
 * DRAW CIRCLE
 * Draws a circle
 *  INPUT center    The center of the circle
 *        radius    How large the cirle is
 * 
 *  Modified from: github linusthe3rd's circles.cpp
 *  Has commented out code for a filled circle
 *************************************************************************/
void drawCircle(const Position& center, const double radius)
{
    // Hollow circle, want to draw expected orbit
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    
    // Draw in red
    glColor3f(RGB_RED[0], RGB_RED[1], RGB_RED[2]);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= lineAmount; i++) {
        glVertex2f(
            center.getPixelsX() + (radius * cos(i * twicePi / lineAmount)),
            center.getPixelsY() + (radius * sin(i * twicePi / lineAmount))
        );
    }

    glEnd();
    
}

/******************************************************************
 * RANDOM
 * This function generates a random number.  
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max)
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);

   return num;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.  
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the double
 ****************************************************************/
double random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   
   assert(min <= num && num <= max);

   return num;
}