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
//#include "position.h"   // for POINT
#include "simulator.h"  // The orbit simulator

// Specific Satellites
#include "hubble.h"
#include "starlink.h"
#include "sputnik.h"

using namespace std;

#include "spaceshipTest/testRunner.cpp" // Test cases, not a class

// To show goal orbit and distance from Earth
// Better to leave as a bool, or comment out?
const bool SHOW_TESTING_VISUALS = false;

// Constants for GEO Orbit
const double GEO_HEIGHT = 35786000.0 + EARTH_RADIUS; // GEO orbit, items here should match Earth's rotation
const double GEO_VELOCITY_X = -3100.0;  // moving 3.1 km/s (to the left in this example)

/*************************************
* Given an Object pointer, calls the correct draw function
*  **************************************/
void drawObjectFunc(const Object* obj)
{
   string objType = typeid(*obj).name();
   //cout << typeid(*obj).name() << ": " << sizeof(obj->getVisual()) << ' ';

   // Neato. Can now draw objects by copying their draw function into the Object..
   // so yeah, GPS will all have their own draw method, meaning they will be a class of their own
   // Unless, can pass 2D int array of colors (see earth) and then make vector<ColorRect> all the same?

   // TEST: Draw based on obj type, instead of rewriting the entire Draw class
   if (objType == "class Spaceship")
      drawShip(obj->getPosition(), obj->getRotation().getDegree(), ((Spaceship*)obj)->getThrust());
   else if (objType == "class Bullet")
      drawProjectile(obj->getPosition());
   else if (objType == "class Earth")
      drawEarth(obj->getPosition(), obj->getRotation().getDegree());
   else if (objType == "class Star")
      drawStar(obj->getPosition(), ((Star*)obj)->getPhase());
   
   // Draw Sputnik
   else if (objType == "class Sputnik")
      drawSputnik(obj->getPosition(), obj->getRotation().getDegree());

   // Draw StarLink and it's Parts
   else if (objType == "class Starlink")
      drawStarlink(obj->getPosition(), obj->getRotation().getDegree());
   else if (objType == "class StarlinkBody")
      drawStarlinkBody(obj->getPosition(), obj->getRotation().getDegree());
   else if (objType == "class StarlinkArray")
      drawStarlinkArray(obj->getPosition(), obj->getRotation().getDegree());

   // Draw Hubble and it's Parts
   else if (objType == "class Hubble")
      drawHubble(obj->getPosition(), obj->getRotation().getDegree());
   else if (objType == "class HubbleComputer")
      drawHubbleComputer(obj->getPosition(), obj->getRotation().getDegree());
   else if (objType == "class HubbleLeft")
      drawHubbleLeft(obj->getPosition(), obj->getRotation().getDegree());
   else if (objType == "class HubbleRight")
      drawHubbleRight(obj->getPosition(), obj->getRotation().getDegree());
   
   // Generic drawings, shouldn't be used
   else if (objType == "class Satellite")
      drawHubble(obj->getPosition(), obj->getRotation().getDegree());
   else if (objType == "class Part")
      drawHubbleTelescope(obj->getPosition(), obj->getRotation().getDegree());
   
   // Draw Fragments
   else if (objType == "class Fragment")
      drawFragment(obj->getPosition(), obj->getRotation().getDegree());
   
   else
   {
      // ERROR: No drawing instance for object
   }
}

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

   // Get user input
   pSim->getInput(pUI);
 
   // Update all Objects in the Simulation
   pSim->update();

   //
   // draw everything
   //

   // For every item in the simulator,
   vector<Object*> simObjects = pSim->getObjects();
   for (vector<Object*>::iterator it = simObjects.begin(); it != simObjects.end(); it++)
   {
      // Draw the Object based on its class type
      drawObjectFunc(*it);

      if (SHOW_TESTING_VISUALS)
      {
         // TEST: draw a circle around each Collision Obj
         try
         {
            //drawRadius((*it)->getPosition(), ((CollisionObject*)*it)->getRadius());
            drawCircle((*it)->getPosition(), ((CollisionObject*)*it)->getRadius());
         }
         catch (exception e) {} // Obj was not able to convert to Collision Obj
      }
   }   
}

/*************************************
* Adds Objects to the simulator
* TODO: Could move to Simulator, but mainly here for testing
*  **************************************/
void addObjects(Simulator* s)
{
   //s->addCollider(new Hubble(Position(0.0, GEO_HEIGHT), Velocity(-3100.0, 0.0)));
   
   //s->addCollider(new StarlinkBody(Position(-10888386.068, 40737174.459), Velocity(-3100.0, 0.0)));
   
   // Added quicker collision
   //s->addCollider(new Hubble(Position(-13595100.4029, 39923965.84268), Velocity(2938.822, 984.102)));

   //s->addCollider(new Starlink(Position(-GEO_HEIGHT, 0.0), Velocity(0.0, 3100.0)));
   //s->addCollider(new HubbleLeft(Position(0.0, -GEO_HEIGHT), Velocity(0.0, 3000.0)));
   //s->addCollider(new Hubble(Position(GEO_HEIGHT, -GEO_HEIGHT), Velocity(-3100.0, 0.0)));

   /* Actual Objects to add: */

   // Starlink
   s->addCollider(new Starlink(Position(-36515095.13, 21082000.0), Velocity(2050.0, 2684.68)));

   // GPS
   s->addCollider(new Hubble(Position(0.0, 26560000.0), Velocity(-3880.0, 0.0)));
   s->addCollider(new Hubble(Position(23001634.72, 13280000.0), Velocity(-1940.00, 3360.18)));
   s->addCollider(new Hubble(Position(23001634.72, -13280000.0), Velocity(1940.00, 3360.18)));
   s->addCollider(new Hubble(Position(0.0, -26560000.0), Velocity(3880.0, 0.0)));
   s->addCollider(new Hubble(Position(-23001634.72, -13280000.0), Velocity(1940.00, -3360.18)));
   s->addCollider(new Hubble(Position(-23001634.72, 13280000.0), Velocity(-1940.00, -3360.18)));

   // Hubble
   s->addCollider(new Hubble(Position(0.0, -42164000.0), Velocity(3100.0, 0.0)));

   // Dragon
   s->addCollider(new Hubble(Position(0.0, 8000000.0), Velocity(-7900.0, 0.0)));

   // StarLink
   s->addCollider(new Hubble(Position(0.0, -13020000.0), Velocity(5800.0, 0.0)));
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
   // Unit Tests - add back in when Collisions work again
   testRunner();

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(DEFAULT_ZOOM); /* 128km equals 1 pixel */
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Orbit Lab",   /* name on the window */
      ptUpperRight);

   // Initialize the Simulator
   Simulator sim = Simulator();
   addObjects(&sim);

   // set everything into action
   ui.run(callBack, &sim);

   return 0;
}
