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

#include "simulator.h"  // The orbit simulator

using namespace std;

#include "spaceshipTest/testRunner.cpp" // Test cases, not a class
//#include "testRunner.cpp" // Test cases, without folder

// To show collision circles
const bool SHOW_TESTING_VISUALS = false;

/*************************************
* Given an Object pointer, calls the correct draw function
*  **************************************/
void drawObjectFunc(const Object* obj)
{
   string objType = typeid(*obj).name();
   //cout << typeid(*obj).name() << ": " << sizeof(obj->getVisual()) << ' ';

   // TODO: Should colorRects/Shapes be used instead?

   // Draws based on obj type, instead of rewriting the entire Draw class
   if (objType == "class Spaceship")
      drawShip(obj->getPosition(), obj->getRotation().getDegree(), ((Spaceship*)obj)->getThrust());
   else if (objType == "class Bullet")
      drawProjectile(obj->getPosition());
   else if (objType == "class Earth")
   {
      drawEarth(obj->getPosition(), obj->getRotation().getDegree());

      //drawObject(obj); // ERROR: rotates drawing around incorrect point
   }
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
   else if (objType == "class HubbleTelescope")
      drawHubbleTelescope(obj->getPosition(), obj->getRotation().getDegree());
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
      // ERROR: No drawing instance for object,
      //   output which class is missing a draw case
      cout << "Unidentified " << objType << endl;
      assert(false);
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

   // Draw every item in the simulator
   vector<Object*> simObjects = pSim->getObjects();
   for (vector<Object*>::iterator it = simObjects.begin(); it != simObjects.end(); it++)
   {
      // Draw the Object based on its class type
      drawObjectFunc(*it);

      // TEST: draw a circle around each Collision Obj
      if (SHOW_TESTING_VISUALS)
      {         
         try
         {            
            drawDirection((*it)->getPosition(), ((CollisionObject*)*it)->getRadius(), (*it)->getRotation()); // Line of direction
            drawCircle((*it)->getPosition(), ((CollisionObject*)*it)->getRadius()); // Collision Circle
         }
         catch (exception e) {} // Obj was not able to convert to Collision Obj
      }
   }   

   drawStar(Position(GEO_HEIGHT, 0), 209);
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

   // set everything into action
   ui.run(callBack, &sim);

   return 0;
}
