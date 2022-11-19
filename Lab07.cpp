/*************************************************************
 * Name:
 *      Orbit
 * Authors:
 *      Ashley DeMott, Logan Huston
 *****************************************************************/

#include <cmath>
#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POINT
#include "simulator.h"

#include "hubble.h"

using namespace std;

#include "spaceshipTest/testRunner.cpp" // Not a class

// To show goal orbit and distance from Earth
// Better to leave as a bool, or comment out?
const bool SHOW_TESTING_VISUALS = true;

// Constants for GEO Orbit
const double GEO_HEIGHT = 35786000.0 + EARTH_RADIUS; // GEO orbit, items here should match Earth's rotation
const double GEO_VELOCITY_X = -3100.0;  // moving 3.1 km/s (to the left in this example)

/*
* Creating a Satelite, made of Parts
* 
vector<pixel> HubbleVisual1 = { Pixel(), ...};
vector<pixel> HubbleVisual2 = { Pixel(), ...};

Part HubblePart1 = Part(offset, rotaion, HubbleVisual1);
Part HubblePart2 = Part(offset, rotation, HubbleVisual2);

Satelite Hubble(startPosition, rotation, {HubblePart1, HubblePart2})
Satelite Hubble(startPosition, rotation, { HubblePart1, HubblePart2 }, startingVelocity);

3 Types of collisions:

Earth - does nothing upon collision
Fragment - destroyed upon collision

New: Fragmented Object
- A type of collision object that fragments into smaller pieces upon collision
- Has number of Fragments to break into (and Satelite has a collection of Parts)
- Would include Satelite and Part (siblings)

*/

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator* pSim = (Simulator*)p;

   //
   // accept input
   //

   // move by a little
   double shipX = 0.0;
   double shipY = 0.0;

   if (pUI->isUp())
      shipY = 1.0;
   if (pUI->isDown())
      shipY = -1.0;
   if (pUI->isLeft())
      shipX = -1.0;
   if (pUI->isRight())
      shipX = 1.0;

   pSim->moveShip(shipX, shipY);

   //
   // perform all the game logic
   //

   // Update all Objects
   pSim->update();

   //
   // draw everything
   //

   vector<Object*> simObjects = pSim->getObjects();
   int numObjs = 0;
   for (vector<Object*>::iterator it = simObjects.begin(); it != simObjects.end(); it++)
   {
      // DEBUG: Get Object type and number of ColorRects
      Object* obj = *it;


      //cout << typeid(*obj).name() << ": " << sizeof(obj->getVisual()) << ' ';
      
      string objType = typeid(*obj).name();


      // TEST: Draw based on obj type, instead of rewriting the entire Draw class
      if(objType == "class Spaceship")
      {
         drawRadius(obj->getPosition(), ((CollisionObject*)obj)->getRadius());
         drawShip(obj->getPosition(), obj->getAngle().getDegree(), ((Spaceship*)obj)->getThrust());
      }
      else if(objType == "class Earth")
      {
         // ERROR: Earth is not rotating
         drawEarth(obj->getPosition(), obj->getAngle().getDegree());
      }
      else if (objType == "class Star")
      {
         drawStar(obj->getPosition(), ((Star*)obj)->getPhase());
      }
      else if (objType == "class Hubble")
      {
         drawHubble(obj->getPosition(), obj->getAngle().getDegree());
      }
      else if (objType == "class HubbleComputer")
      {
         drawHubbleComputer(obj->getPosition(), obj->getAngle().getDegree());
      }
      else if (objType == "class HubbleLeft")
      {
         drawHubbleLeft(obj->getPosition(), obj->getAngle().getDegree());
      }
      else if (objType == "class HubbleRight")
      {
         drawHubbleRight(obj->getPosition(), obj->getAngle().getDegree());
      }
      else if (objType == "class Satellite")
      {
         drawRadius(obj->getPosition(), ((CollisionObject*)obj)->getRadius());
         drawHubble(obj->getPosition(), obj->getAngle().getDegree());
      }
      else if (objType == "class Part")
      {
         drawHubbleTelescope(obj->getPosition(), obj->getAngle().getDegree());
      }
      else if (objType == "class Fragment")
      {
         drawFragment(obj->getPosition(), obj->getAngle().getDegree());
      }
      else
      {
         // ERROR: No drawing instance for object
      }

      // Draw the ColorRects of the Object
      // So far, Earth is the only one that draws, Spaceship in progress
      //drawObject(obj);
   }

   //drawCircle(0.0, 50000.0);
   drawCircle(Position(0.0, 0.0), GEO_HEIGHT);
   drawStar(Position(0.0, EARTH_RADIUS * 1.5), 1);
   //drawStar(GEO_HEIGHT, GEO_HEIGHT);

   //drawShip(Position(0, GEO_HEIGHT), 0, 1);

   // Neato. Can now draw objects by copying their draw function into the Object..
   // so yeah, GPS will all have their own draw method, meaning they will be a class of their own
   // Unless, can pass 2D int array of colors (see earth) and then make vector<ColorRect> all the same?
   //drawEarth(Position(50000000, 50000000), 0);
}

void addObjects(Simulator* s)
{
   s->addCollider(new Satellite(Position(0.0, GEO_HEIGHT), Velocity(-3100.0, 0.0)));
   s->addCollider(new Satellite(Position(-GEO_HEIGHT, 0.0), Velocity(0.0, 3100.0)));

   s->addCollider(new Satellite(Position(0.0, -GEO_HEIGHT), Velocity(0.0, 3000.0)));

   s->addCollider(new Hubble(Position(GEO_HEIGHT, -GEO_HEIGHT), Velocity(-3100.0, 0.0)));
}

double TwoDValue::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Unit Tests
   testRunner();

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Orbit Lab",   /* name on the window */
      ptUpperRight);

   // *TODO: Give Simulator upper right? Or draw even if off canvas?

   // Initialize the Simulator
   Simulator sim = Simulator();
   addObjects(&sim);

   // set everything into action
   ui.run(callBack, &sim);

   return 0;
}
