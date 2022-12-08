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

#include "position.h"
#include "uiDraw.h"
#include "colorRect.h"

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
 * DRAW PROJECTILE
 * Draw a projectile on the screen at a given point.
 *   INPUT  pt     The location of the projectile
 *************************************************************************/
void drawProjectile(const Position& pt)
{
   ColorRect rects[] =
   {
      {1,1, -1,1, -1,-1, 1,-1, RGB_WHITE },
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(pt, Position(), rects[i], 0.0);
}

/************************************************************************
 * DRAW FRAGMENT
 * Draw a fragment on the screen.
 *   INPUT  center    The location of the fragment
 *          rotation  Which angle it is pointed
 *************************************************************************/
void drawFragment(const Position& center, double rotation)
{
   ColorRect rects[] =
   {
      {-4,1, -4,-1, 4,-1, 4,1, RGB_LIGHT_GREY },
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, Position(), rects[i], rotation);
}

/************************************************************************
 * DRAW Crew Dragon Center
 * Draw the center part of the Crew Dragon module
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void drawCrewDragonCenter(const Position& center, double rotation)
{
   ColorRect rects[] = 
   {
      {-5,5,   3,5,   3,-5,  -5,-5,  RGB_LIGHT_GREY },
      { 3,5,   3,-5, 11,-3,  11,3,   RGB_GREY },
      {12,-3, 12,3,  11,-3,  11,3,   RGB_DARK_GREY },
      { 4,3,   7,2,   7,-2,   4,-3,  RGB_DARK_GREY}
   };

   for (int i = 0; i < sizeof(rects)/sizeof(ColorRect); i++)
      glDrawRect(center, Position(), rects[i], rotation);
}

/************************************************************************
 * DRAW Crew Dragon Right array
 * Draw the right solar array of the crew dragon module
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void drawCrewDragonRight(const Position& center, double rotation, const Position& offset)
{
   ColorRect rects[] =
   {
      {-4,5,  4,5,  4,1,  -4,1,  RGB_DEEP_BLUE },
      {-4,-1, 4,1,  4,-5, -4,-5, RGB_DEEP_BLUE },
      {0,2,   0,-6, 1,-6,  1,2,  RGB_GREY },
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, offset, rects[i], rotation);
}

/************************************************************************
 * DRAW Crew Dragon Left array
 * Draw the left solar array of the crew dragon module
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void drawCrewDragonLeft(const Position& center, double rotation, const Position& offset)
{
   ColorRect rects[] =
   {
      {-4,5,  4,5,  4,1,  -4,1,  RGB_DEEP_BLUE },
      {-4,-1, 4,1,  4,-5, -4,-5, RGB_DEEP_BLUE },
      {0,2,   0,-6, 1,-6,  1,2,  RGB_GREY }
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, offset, rects[i], rotation);
}


/************************************************************************
 * DRAW Crew Dragon
 * Draw a crew dragon on the screen. It consists of three components
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void drawCrewDragon(const Position& center, double rotation)
{
   drawCrewDragonCenter(center, rotation);

   Position posRight;
   posRight.setPixelsX(-1.0);
   posRight.setPixelsY(11.0);
   drawCrewDragonRight( center, rotation, posRight);
   
   Position posLeft;
   posLeft.setPixelsX(-1.0);
   posLeft.setPixelsY(-11.0);
   drawCrewDragonLeft(  center, rotation, posLeft);
}

/************************************************************************
 * DRAW Sputnik
 * Draw the satellite on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void drawSputnik(const Position& center, double rotation)
{
   // draw the sphere                                               
   const PT pointsSphere[] =
   {
      {0,0},
      {2,6}, {6,2}, {6,-2}, {2,-6}, {-2,-6}, {-2,-6}, {-6,-2}, {-6,2}, {-2,6}, {2,6}
   };
   glBegin(GL_TRIANGLE_FAN);
   glColor(RGB_GREY);
   for (int i = 0; i < sizeof(pointsSphere) / sizeof(PT); i++)
      glVertexPoint(rotate(center, pointsSphere[i].x, pointsSphere[i].y, rotation));
   glEnd();

   // draw the antenna
   glBegin(GL_LINES);
   glColor(RGB_WHITE);
   glVertexPoint(rotate(center,  -6.0,   2.0, rotation));
   glVertexPoint(rotate(center, -10.0, -15.0, rotation));

   glVertexPoint(rotate(center,  0.0,   1.0, rotation));
   glVertexPoint(rotate(center, -2.5, -15.0, rotation));

   glVertexPoint(rotate(center,  2.0, -6.0, rotation));
   glVertexPoint(rotate(center,  2.5, -15.0, rotation));

   glVertexPoint(rotate(center,  6.0,  2.0, rotation));
   glVertexPoint(rotate(center, 10.0, -15.0, rotation));
   glEnd();
}

/************************************************************************
 * DRAW GPS Left
 * Draw a GPS satellite left solar array on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void drawGPSLeft(const Position& center, double rotation, const Position& offset)
{
   ColorRect rects[] =
   {
      {-6,5,  6,5,  6,1,  -6,1,  RGB_WHITE},
      {-6,0,  6,0,  6,-4, -6,-4, RGB_WHITE},
      {-5,4,  5,4,  5,2,  -5,2,  RGB_DEEP_BLUE },
      {-5,-1, 5,-1, 5,-3, -5,-3, RGB_DEEP_BLUE }
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, offset, rects[i], rotation);

   // draw the line connecting the solar array to the rest of the ship
   glBegin(GL_LINE_STRIP);
   glColor(RGB_WHITE);
   glVertexPoint(rotate(center,
                        3.0 + offset.getPixelsX(),
                        4.0 + offset.getPixelsY(),
                        rotation));
   glVertexPoint(rotate(center,
                        0.0 + offset.getPixelsX(),
                        8.0 + offset.getPixelsY(),
                        rotation));
   glVertexPoint(rotate(center,
                        -3.0 + offset.getPixelsX(),
                        4.0 + offset.getPixelsY(),
                        rotation));
   glEnd();
}

/************************************************************************
 * DRAW GPS Right
 * Draw a GPS satellite right solar array on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void drawGPSRight(const Position& center, double rotation, const Position& offset)
{
   ColorRect rects[] =
   {
      {-6,-5, 6,-5, 6,-1, -6,-1,  RGB_WHITE},
      {-6,0,  6,0,  6,4,  -6,4,   RGB_WHITE},
      {-5,-4, 5,-4, 5,-2, -5,-2,  RGB_DEEP_BLUE },
      {-5,1,  5,1,  5,3,  -5,3,   RGB_DEEP_BLUE }
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, offset, rects[i], rotation);

   // draw the line connecting the solar array to the rest of the ship
   glBegin(GL_LINE_STRIP);
   glColor(RGB_WHITE);
   glVertexPoint(rotate(center,
                        3.0 + offset.getPixelsX(),
                        -4.0 + offset.getPixelsY(),
                        rotation));
   glVertexPoint(rotate(center,
                        0.0 + offset.getPixelsX(),
                        -8.0 + offset.getPixelsY(),
                        rotation));
   glVertexPoint(rotate(center,
                        -3.0 + offset.getPixelsX(),
                        -4.0 + offset.getPixelsY(),
                        rotation));
   glEnd();

}

/************************************************************************
 * DRAW GPS Center
 * Draw the main part of the GPS satellite
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void drawGPSCenter(const Position& center, double rotation)
{
   ColorRect rects[4] =
   {
      {-3,4,  4,4,  4,-4, -3,-4, RGB_GOLD  },
      {4,4,  -3,4, -3,-4, -4,-4, RGB_WHITE },
      {4,3,   7,3,   7,1,   4,1, RGB_GREY  },
      {4,-3, 7,-3,  7,-1,  4,-1, RGB_GREY  }
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, Position(), rects[i], rotation);
}

/************************************************************************
 * DRAW GPS
 * Draw a GPS satellite on the screen. It consists of three parts
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void drawGPS(const Position& center, double rotation)
{
   drawGPSCenter(center, rotation);
   
   Position posRight;
   posRight.setPixelsX(0.0);
   posRight.setPixelsY(12.0);
   drawGPSRight(center, rotation, posRight);
   
   Position posLeft;
   posLeft.setPixelsX(0.0);
   posLeft.setPixelsY(-12.0);
   drawGPSLeft(center,  rotation, posLeft);
}

/************************************************************************
 * DRAW Hubble Telescope
 * Draw a the telescope part of the hubble
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void drawHubbleTelescope(const Position& center, double rotation, const Position& offset)
{
   ColorRect rects[] =
   {
      {-9,3,  11,3,  11,-3, -9,-3,  RGB_LIGHT_GREY},
      {11,3,  15,6,  16,5,  12,2,   RGB_GREY},
      {-9,-2, 11,-2, 11,-3, -9,-3,  RGB_GREY}
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, offset, rects[i], rotation);
}

/************************************************************************
 * DRAW Hubble Computer
 * Draw a the computer part of the hubble space telescope
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
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
}

/************************************************************************
 * DRAW Hubble Left
 * Draw left solar array of the hubble space telescope on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void drawHubbleLeft(const Position& center, double rotation, const Position& offset)
{
   ColorRect rects[] =
   {
      {-8,3, -1,3, -1,-1, -8,-1,  RGB_LIGHT_GREY},
      { 8,3,  1,3,  1,-1,  8,-1,  RGB_LIGHT_GREY},
      {-7,2, -1,2, -2,0,  -7,0,   RGB_DARK_GREY},
      { 7,2,  1,2,  2,0,   7,0,   RGB_DARK_GREY}
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, offset, rects[i], rotation);

   glBegin(GL_LINE_STRIP);
   glColor(RGB_WHITE);
   glVertexPoint(rotate(center,
                        0.0 + offset.getPixelsX(),
                        3.0 + offset.getPixelsY(),
                        rotation));
   glVertexPoint(rotate(center,
                        0.0 + offset.getPixelsX(),
                        -5.0 + offset.getPixelsY(),
                        rotation));
   glEnd();
}


/************************************************************************
 * DRAW Hubble Right
 * Draw right solar array of the hubble space telescope on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void drawHubbleRight(const Position& center, double rotation, const Position& offset)
{
   ColorRect rects[] =
   {
      {-8,-3, -1,-3, -1,1,  -8,1,  RGB_LIGHT_GREY},
      { 8,-3,  1,-3,  1,1,   8,1,  RGB_LIGHT_GREY},
      {-7,-2, -1,-2, -2,0,  -7,0,  RGB_DARK_GREY},
      { 7,-2,  1,-2,  2,0,   7,0,  RGB_DARK_GREY}
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, offset, rects[i], rotation);

   glBegin(GL_LINE_STRIP);
   glColor(RGB_WHITE);
   glVertexPoint(rotate(center,
                        0.0 + offset.getPixelsX(),
                        -3.0 + offset.getPixelsY(),
                        rotation));
   glVertexPoint(rotate(center,
                        0.0 + offset.getPixelsX(),
                        5.0 + offset.getPixelsY(),
                        rotation));
   glEnd();
}

/************************************************************************
 * DRAW Hubble
 * Draw a Hubble satellite on the screen. It consists of 4 parts
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void drawHubble(const Position& center, double rotation)
{
   Position posTelescope;
   posTelescope.setPixelsX(2.0);
   posTelescope.setPixelsY(0.0);
   drawHubbleTelescope(center, rotation, posTelescope);

   Position posComputer;
   posComputer.setPixelsX(-10.0);
   posComputer.setPixelsY(0.0);
   drawHubbleComputer(center,  rotation, posComputer);
   
   Position posRight;
   posRight.setPixelsX(1.0);
   posRight.setPixelsY(-8.0);
   drawHubbleRight(center,     rotation, posRight);

   Position posLeft;
   posLeft.setPixelsX(1.0);
   posLeft.setPixelsY(8.0);
   drawHubbleLeft(center,      rotation, posLeft);
}

/************************************************************************
 * DRAW Starlink Body
 * Draw the body of the Starlink satellite on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void drawStarlinkBody(const Position& center, double rotation, const Position& offset)
{
   ColorRect rects[] =
   {
      {1,5,    1,-3, -1,-5, -1,3,  RGB_LIGHT_GREY},
      {-4,-5, -1,-5, -1,3,  -4,3,  RGB_GREY},
      {-4,3,  -2,3,   1,5,  -1,3,  RGB_WHITE}
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, offset, rects[i], rotation);
}

/************************************************************************
 * DRAW Starlink Array
 * Draw the solar array of the Starlink satellite on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *************************************************************************/
void drawStarlinkArray(const Position& center, double rotation, const Position& offset)
{
   ColorRect rects[] =
   {
      {-7,7, 8,2, 8,-6, -7,-1,  RGB_GREY},
      {-6,6, 7,1, 7,-5, -6,0,   RGB_DEEP_BLUE}
   };

   for (int i = 0; i < sizeof(rects) / sizeof(ColorRect); i++)
      glDrawRect(center, offset, rects[i], rotation);
}

/************************************************************************
 * DRAW Starlink
 * Draw a Starlink satellite on the screen. It consists of 2 components
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void drawStarlink(const Position& center, double rotation)
{
   Position posBody;
   posBody.setPixelsX(-1.0);
   posBody.setPixelsY(0.0);
   drawStarlinkBody(center,  rotation, posBody);

   Position posArray;
   posArray.setPixelsX(8.0);
   posArray.setPixelsY(-2.0);
   drawStarlinkArray(center, rotation, posArray);
}

/************************************************************************
 * DRAW Ship
 * Draw a spaceship on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is pointing
 *        thrust    Whether the thrusters are on
 *************************************************************************/
void drawShip(const Position& center, double rotation, bool thrust)
{
   // draw the white part of the ship                                               
   const PT pointsShipWhite[] =
   { 
      {0,0},
      {-3,-9}, {-12,-12}, {-14,-12}, {-13,-7}, {-8,-2}, {-6,3}, {-4,11}, {-4,14}, {-3,16}, {-1,18},
      {1,18}, {3,16}, {4,14}, {4,11}, {6,3}, {8,-2}, {13,-7}, {14,-12}, {12,-12}, {3,-9}, {-3,-9}
   };

   glBegin(GL_TRIANGLE_FAN);
   glColor(RGB_LIGHT_GREY);
   for (int i = 0; i < sizeof(pointsShipWhite) / sizeof(PT); i++)
      glVertexPoint(rotate(center, pointsShipWhite[i].x, pointsShipWhite[i].y, rotation));
   glEnd();

   // draw the flame if necessary
   if (thrust)
   {
      glBegin(GL_TRIANGLES);
      glColor(RGB_RED);
      glVertexPoint(rotate(center, -3.0, -9.0, rotation));
      glVertexPoint(rotate(center, random(-5.0, 5.0), random(-25.0, -13.0), rotation));
      glVertexPoint(rotate(center, 3.0, -9.0, rotation));
      glVertexPoint(rotate(center, -3.0, -9.0, rotation));
      glVertexPoint(rotate(center, random(-5.0, 5.0), random(-25.0, -13.0), rotation));
      glVertexPoint(rotate(center, 3.0, -9.0, rotation));
      glResetColor();
      glEnd();
   }

   // draw the dark part of the ship                                               
   const PT pointsShipBlack[][4] =
   {
      {{-5,-8},  {-12,-11},{-11,-7},{-5,-2}}, // left wing
      {{ 5,-8},  { 12,-11},{ 11,-7},{ 5,-2}}, // right wing
      {{ 0,-13}, {-3,11},  {-1,15}, {1,15}},  // left canopy
      {{ 0,-13}, { 3,11},  { 1,15}, {-1,15}}  // right canopy
   };
   glBegin(GL_QUADS);
   glColor(RGB_DEEP_BLUE);
   for (int iRectangle = 0; iRectangle < 4; iRectangle++)
      for (int iVertex = 0; iVertex < 4; iVertex++)
      glVertexPoint(rotate(center, pointsShipBlack[iRectangle][iVertex].x, 
                                   pointsShipBlack[iRectangle][iVertex].y, rotation));
   glResetColor();
   glEnd();
}


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
   // TODO: Radius is drawn in Pixels, currently given as Meters
   //double radius = radiusM / 128000.0;

    // Filled circle
    /*
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    double x = center.getPixelsX();
    double y = center.getPixelsY();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }*/
    
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

/************************************************************************
 * DRAW Earth
 * Draw Earth
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *************************************************************************/
void drawEarth(const Position& center, double rotation)
{
   const int * colors[5] = 
   {
      RGB_GREY,  // 0
      RGB_BLUE,  // 1
      RGB_GREEN, // 2
      RGB_TAN,   // 3
      RGB_WHITE  // 4
   };

   int earth[50][50] =
   {
   {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,3,3, 3,2,2,1,1, 1,1,2,2,2, 3,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,1,1,2,2, 2,2,2,2,3, 3,3,3,3,3, 3,3,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,0,0, 0,0,2,1,1, 1,2,2,2,2, 2,2,2,2,2, 2,2,2,2,3, 3,3,3,1,1, 1,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,0,0, 0,2,2,1,1, 2,2,2,2,2, 3,3,3,3,3, 3,3,3,3,3, 2,2,2,2,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0,},

   {0,0,0,0,0, 0,0,0,0,2, 1,1,1,2,2, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,4, 3,3,3,3,3, 3,1,3,3,1, 1,0,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,1,1, 1,1,1,1,3, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,3, 4,3,3,3,3, 3,3,2,3,3, 1,1,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,1,1,1, 1,1,1,1,1, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,1,3, 3,2,2,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,1,1,1,1, 1,1,1,1,1, 2,3,3,3,3, 3,3,3,3,3, 3,3,3,3,2, 3,3,3,3,3, 3,3,3,3,3, 3,3,2,3,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,1,1,1,1, 2,2,2,2,2, 3,3,3,3,3, 3,3,3,3,3, 2,3,3,3,3, 3,3,3,2,3, 3,2,2,3,2, 3,3,3,3,0, 0,0,0,0,0,},

   {0,0,0,0,0, 1,1,1,1,1, 2,1,1,2,3, 3,3,3,3,2, 2,2,2,3,3, 3,2,3,3,3, 3,3,3,3,3, 3,1,3,3,3, 3,3,3,2,3, 0,0,0,0,0,},
   {0,0,0,0,1, 1,1,1,1,1, 2,1,1,3,3, 3,3,3,3,3, 3,2,2,3,2, 2,3,3,3,3, 3,3,3,3,3, 1,1,3,3,3, 3,3,3,3,3, 3,0,0,0,0,},
   {0,0,0,0,1, 1,1,1,1,2, 1,1,3,2,2, 3,2,3,3,3, 2,3,2,2,2, 2,2,2,3,3, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,3, 3,3,0,0,0,},
   {0,0,0,1,1, 1,1,1,1,1, 1,1,2,2,3, 3,3,3,3,3, 2,3,3,3,3, 2,3,3,3,3, 2,2,3,3,3, 3,2,3,2,1, 3,1,1,3,3, 3,3,0,0,0,},
   {0,0,0,1,1, 1,1,1,1,1, 2,2,2,2,3, 3,3,2,2,2, 3,3,3,3,3, 3,3,3,3,2, 2,2,3,2,3, 3,3,3,2,1, 3,3,1,2,3, 3,3,0,0,0,},

   {0,0,1,1,1, 1,1,1,1,1, 1,1,2,2,1, 2,2,2,3,2, 3,3,3,3,3, 3,3,3,3,3, 2,2,2,2,2, 3,3,3,3,2, 1,3,1,1,3, 3,3,3,0,0,},
   {0,0,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 3,2,2,3,3, 3,3,3,3,3, 3,3,4,3,3, 3,2,2,2,2, 3,3,3,3,3, 1,1,3,3,1, 3,3,3,0,0,},
   {0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 3,3,3,3,3, 3,3,3,3,3, 3,3,3,1,1, 1,2,2,2,2, 2,2,3,3,3, 2,3,2,1,2, 3,3,3,2,0,},
   {0,1,1,1,1, 1,1,1,1,1, 2,1,1,1,3, 3,3,3,3,3, 3,3,4,4,3, 1,1,1,1,4, 1,2,2,2,2, 2,2,3,3,3, 3,3,2,1,1, 3,3,3,3,0,},
   {0,1,1,1,1, 1,1,1,1,1, 1,3,2,2,3, 3,3,3,3,1, 1,1,1,4,1, 1,1,1,4,1, 1,1,3,2,2, 2,2,3,3,3, 3,3,1,2,1, 3,3,3,3,0,},

   {0,1,1,1,1, 1,1,1,1,1, 1,2,2,1,3, 3,3,3,3,4, 1,1,1,1,4, 1,1,1,1,1, 1,1,2,2,2, 2,2,1,2,3, 3,2,1,1,1, 3,3,3,3,0,},
   {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,3, 3,3,3,1,4, 1,1,1,1,1, 1,1,1,1,1, 1,1,2,2,2, 2,2,2,2,3, 3,3,3,1,2, 3,3,3,3,3,},
   {1,1,1,1,1, 1,1,1,1,1, 1,1,1,3,3, 3,3,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,3, 3,2,2,2,3, 3,3,2,2,2, 3,3,3,2,2,},
   {1,1,1,1,1, 1,1,1,1,1, 1,1,1,3,3, 3,4,1,1,1, 1,1,1,1,1, 1,1,1,4,4, 4,1,1,1,1, 1,3,3,1,1, 3,3,3,2,1, 3,3,3,3,2,},
   {1,1,1,1,1, 1,1,1,1,1, 1,1,1,2,3, 3,1,1,1,1, 1,1,1,1,1, 1,1,4,4,4, 4,4,4,1,1, 1,1,1,1,1, 1,3,3,3,1, 3,3,3,3,2,},

   {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 3,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,2,3, 3,3,1,3,3, 3,3,3,3,2,},
   {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,4,4,1, 1,1,1,1,1, 1,1,1,1,2, 1,1,1,3,3, 3,3,3,3,2,},
   {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,4,1,1,1, 1,1,1,1,1, 1,1,4,4,4, 4,1,1,1,1, 1,1,1,1,2, 1,1,1,3,2, 3,3,3,3,2,},
   {1,1,1,1,1, 1,1,1,1,1, 1,1,1,3,2, 2,2,2,1,1, 1,1,1,1,4, 4,4,4,4,4, 4,4,4,1,4, 1,1,1,1,1, 1,1,1,1,1, 1,3,3,3,3,},
   {0,1,1,1,1, 1,1,1,1,1, 1,1,1,2,2, 2,3,3,1,1, 1,1,1,4,4, 4,1,4,4,4, 4,4,4,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,3,3,3,0,},

   {0,1,1,1,1, 1,1,1,1,1, 1,1,1,3,2, 2,2,3,1,1, 1,1,4,1,1, 4,1,1,4,4, 4,4,4,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,2,3,3,0,},
   {0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,3, 2,2,2,2,4, 1,4,1,1,4, 4,1,1,1,1, 4,4,4,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,2,1,0,},
   {0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 3,2,2,2,2, 2,2,4,4,4, 2,4,4,1,1, 4,4,4,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,0,},
   {0,0,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 2,2,2,3,2, 3,2,2,1,4, 2,4,4,4,1, 1,1,4,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,0,0,},
   {0,0,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 3,3,3,3,3, 3,3,3,3,3, 2,2,2,4,4, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,0,0,},

   {0,0,0,1,1, 1,1,1,1,1, 1,1,1,1,1, 2,3,2,2,2, 3,3,3,2,2, 2,1,2,2,2, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,0,0,0,},
   {0,0,0,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,2,2,2,2, 3,1,3,2,2, 1,1,2,3,2, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,0,0,0,},
   {0,0,0,0,1, 1,1,1,1,1, 1,1,1,1,1, 2,2,2,2,2, 3,3,3,3,2, 1,1,1,3,2, 2,3,2,2,1, 1,1,1,1,1, 1,1,1,1,1, 1,0,0,0,0,},
   {0,0,0,0,1, 1,1,1,1,1, 1,1,1,1,1, 1,3,2,2,3, 3,3,3,3,3, 1,1,2,2,2, 2,2,2,2,3, 1,1,1,1,1, 1,1,1,1,1, 1,0,0,0,0,},
   {0,0,0,0,0, 1,1,1,1,1, 1,1,1,1,1, 2,3,2,3,3, 3,3,3,3,3, 2,2,1,2,2, 2,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0,},

   {0,0,0,0,0, 0,1,1,1,1, 1,1,1,1,2, 3,2,2,3,3, 3,3,3,2,2, 2,2,2,2,2, 1,2,2,1,1, 1,1,1,1,1, 1,1,1,1,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,1,1,1, 1,1,1,1,2, 3,3,3,3,3, 3,1,3,2,2, 1,2,2,2,2, 2,2,1,1,1, 1,1,1,1,1, 1,1,1,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,1,1, 1,1,1,1,1, 3,3,3,3,3, 3,3,3,3,2, 2,2,2,2,2, 2,1,1,1,1, 1,1,1,1,1, 1,1,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,0,1, 1,1,1,1,1, 2,3,3,3,3, 3,3,3,3,3, 3,3,3,2,2, 1,1,1,1,1, 1,1,1,1,1, 1,0,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,0,0, 1,1,1,1,1, 1,1,3,3,3, 3,3,3,3,3, 3,3,2,2,2, 1,1,1,1,1, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0,},

   {0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,1, 1,2,3,3,3, 3,3,3,2,3, 2,2,2,2,1, 1,1,1,1,1, 1,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 1,1,1,3,3, 3,3,3,2,1, 1,1,2,2,2, 1,1,1,1,2, 1,2,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,1,1,1,3, 3,3,1,1,1, 1,1,1,2,2, 2,2,1,1,3, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,1, 1,2,2,2,2, 1,1,1,1,1, 1,2,3,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
   {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,1, 1,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
   };

   const double SCALE = 2.0;

   for (int y = 0; y < 50; y++)
      for (int x = 0; x < 50; x++)
         if (earth[y][x])
         {
            assert(earth[y][x] > 0 && earth[y][x] <= 4);
            ColorRect rect = 
            {
               static_cast<int>(x * SCALE),
               static_cast<int>(y * SCALE),
               
               static_cast<int>(x * SCALE),
               static_cast<int>(y * SCALE + SCALE),
               
               static_cast<int>(x * SCALE + SCALE),
               static_cast<int>(y * SCALE + SCALE),
               
               static_cast<int>(x * SCALE + SCALE),
               static_cast<int>(y * SCALE), colors[earth[y][x]]};
            Position pos;
            pos.setPixelsX(-25.0 * SCALE);
            pos.setPixelsY(-25.0 * SCALE);
            glDrawRect(center, pos, rect, rotation);
         }

   return;
}

/************************************************************************
 * DRAW STAR
 * Draw a star that twinkles
 *   INPUT  POINT     The position of the beginning of the star
 *          PHASE     The phase of the twinkling
 *************************************************************************/
void drawStar(const Position& point, unsigned char phase)
{
   // Get ready...
   glBegin(GL_POINTS);

   // most of the time, it is just a pale yellow dot
   if (phase < 128)
   {
      glColor3f((GLfloat)0.5 /* red % */, (GLfloat)0.5 /* green % */, (GLfloat)0.0 /* blue % */);
      glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 0.0));
   }
   // transitions to a bright yellow dot
   else if (phase < 160 || phase > 224)
   {
      glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)0.0 /* blue % */);
      glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 0.0));
   }
   // transitions to a bright yellow dot with pale yellow corners
   else if (phase < 176 || phase > 208)
   {
      glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)0.0 /* blue % */);
      glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 0.0));
      glColor3f((GLfloat)0.5 /* red % */, (GLfloat)0.5 /* green % */, (GLfloat)0.0 /* blue % */);
      glVertex2f((GLfloat)(point.getPixelsX() + 1.0), (GLfloat)(point.getPixelsY() + 0.0));
      glVertex2f((GLfloat)(point.getPixelsX() - 1.0), (GLfloat)(point.getPixelsY() + 0.0));
      glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 1.0));
      glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() - 1.0));
   }
   // the biggest yet
   else
   {
      glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)0.0 /* blue % */);
      glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 0.0));
      glColor3f((GLfloat)0.7 /* red % */, (GLfloat)0.7 /* green % */, (GLfloat)0.0 /* blue % */);
      glVertex2f((GLfloat)(point.getPixelsX() + 1.0), (GLfloat)(point.getPixelsY() + 0.0));
      glVertex2f((GLfloat)(point.getPixelsX() - 1.0), (GLfloat)(point.getPixelsY() + 0.0));
      glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 1.0));
      glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() - 1.0));
      glColor3f((GLfloat)0.5 /* red % */, (GLfloat)0.5 /* green % */, (GLfloat)0.0 /* blue % */);
      glVertex2f((GLfloat)(point.getPixelsX() + 2.0), (GLfloat)(point.getPixelsY() + 0.0));
      glVertex2f((GLfloat)(point.getPixelsX() - 2.0), (GLfloat)(point.getPixelsY() + 0.0));
      glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() + 2.0));
      glVertex2f((GLfloat)(point.getPixelsX() + 0.0), (GLfloat)(point.getPixelsY() - 2.0));
   }

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
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