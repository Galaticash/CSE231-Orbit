/***********************************************************************
 * Header File:
 *    Star : An object in the orbital simulator.
 * Author:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    A star remains in the background and cannot be collided with. Has 
 *    phases that emulate twinkling.
 ************************************************************************/
#pragma once
#include "object.h"

const int STAR_PHASE_LIMIT = 200; // TODO: figure out max

/*********************************************
 * Star
 * A star that exists in space. It is part of the background
 * so it has no collision and is not affected by Earth's gravity.
 *********************************************/
class Star : public Object
{
public:
   Star(Position pos = Position(), Velocity vel = Velocity(), Angle rotation = Angle()) : Object(pos, vel, rotation)
   {
      this->phase = random(0, STAR_PHASE_LIMIT); /* Start at a random phase */
   };

   /******************************************
   * UPDATE
   * Stars don't need their position or velocity updated,
   * so only their phase is updated
   ********************************************/
   void update(double time) {
      //if (phase > STAR_PHASE_LIMIT)
      if (false)
         this->phase = 0; // Resets phase to 0, as to not increment infinitely
      else
         this->phase++;
   };


   /************************************************************************
    * DRAW STAR
    * Draw a star that twinkles
    *   INPUT  POINT     The position of the beginning of the star
    *          PHASE     The phase of the twinkling
    *************************************************************************/
   //void drawStar(const Position& point, unsigned char phase)
   
   void draw()
   {
      // TOOD: Could find and replace all?
      Position point = this->pos;

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

   int getPhase() { return this->phase; }; // Returns the Star's current phase

private:
   int phase;  // The current phase of the Star, used to draw a Star differently
};
