/*************************************************************
 * Name:
 *    Main : The entry point for the orbital simulator.
 * Authors:
 *    Ashley DeMott, Logan Huston
 * Summary:
 *    Starts the orbital simulator and runs the callback and drawing.
 *****************************************************************/

#include "simulator.h"  // The orbit simulator

#include "spaceshipTest/testRunner.cpp" // Test cases, not a class
//#include "testRunner.cpp" // Test cases, without folder

// The default zoom value for the program,
const double DEFAULT_ZOOM = 128000.0 /* 128km equals 1 pixel */;

// The Interface's window size
const double SCREEN_SIZE = 1000.0; // The size of the window (currenly square)
const double SCREEN_SIZE_X = SCREEN_SIZE; // The horizonal length of the window
const double SCREEN_SIZE_Y = SCREEN_SIZE; // The vertical length of the window

using namespace std;

/*************************************
* DRAW OBJECT
* Given an Object pointer, calls the correct draw function in uiDraw
***************************************/
void drawObject(const Object* obj, bool debug = false)
{
   string objType = typeid(*obj).name();
   // DEBUG: cout << typeid(*obj).name() << ": " << sizeof(obj->getVisual()) << ' ';

   // DEBUG: To draw Debug tools (collision Radius and Rotation Angle)
   if (debug)
   {
      // Don't draw for smaller Objects or the Earth
      if (objType != "class Star" 
         //&& objType != "class Fragment" 
         && objType != "class Bullet" && objType != "class Earth")
      {
         // Draw Direction and Radius
         double radius = objType == "class Fragment" ? 10 : 15;
         //double radius = 15;

         //drawDirection((obj)->getPosition(), 15, (obj)->getRotation()); // Facing direction
         drawDirection((obj)->getPosition(), radius, (obj)->getVelocity().getAngle()); // Velocity direction
         drawCircle((obj)->getPosition(), 1); // Object's Position Point
      }
   }
   
   // Draws based on obj type, instead of rewriting the entire Draw class
   if (objType == "class Spaceship")
   {
      // DEBUG: Show Position, Velocity, and Rotation Angle
      if (debug)
      {
         // DEBUG: Extra debug for Spaceship's Position, Velocity, Rotation, etc
         Position textPos;
         double buffer = 10;
         double textSize = 12;
         textPos.setPixelsX(-(SCREEN_SIZE_X / 2) + buffer);
         textPos.setPixelsY((SCREEN_SIZE_Y / 2) - buffer - textSize);

         /*
         string posX = to_string(obj->getPosition().getMetersX());
         string posY = to_string(obj->getPosition().getMetersY());
         string pos = "Position: (" + posX.substr(0, posX.find(".") + 3) + ", " + posY.substr(0, posY.find(".") + 3) + ")";
         drawText(textPos, (pos).c_str());

         textPos.addPixelsY(-textSize * 2.0);

         string velX = to_string(obj->getVelocity().getMetersX());
         string velY = to_string(obj->getVelocity().getMetersY());
         string vel = "Velocity: (" + velX.substr(0, velX.find(".") + 3) + ", " + velY.substr(0, velY.find(".") + 3) + ")";
         drawText(textPos, (vel).c_str());

         textPos.addPixelsY(-textSize * 2.0);

         string rRad = to_string(obj->getRotation().getRadian());
         string rDeg = to_string(obj->getRotation().getDegree());
         string rotation = "Rotation: " + rRad.substr(0, rRad.find(".") + 3) + " radians or " + rDeg.substr(0, rDeg.find(".") + 3) + " degrees";
         drawText(textPos, (rotation).c_str());

         textPos.addPixelsY(-textSize * 2.0);

         string vRad = to_string(obj->getVelocity().getAngle().getRadian());
         string vDeg = to_string(obj->getVelocity().getAngle().getDegree());
         string vRotation = "Velocity Angle: " + vRad.substr(0, vRad.find(".") + 3) + " radians or " + vDeg.substr(0, vDeg.find(".") + 3) + " degrees";
         drawText(textPos, (vRotation).c_str());*/        
      }

      drawShip(obj->getPosition(), obj->getRotation().getRadian(), ((Spaceship*)obj)->getThrust());
   }
   else if (objType == "class Bullet")
      drawProjectile(obj->getPosition());
   else if (objType == "class Earth")
      drawEarth(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class Star")
      drawStar(obj->getPosition(), ((Star*)obj)->getPhase());

   // Draw Sputnik
   else if (objType == "class Sputnik")
      drawSputnik(obj->getPosition(), obj->getRotation().getRadian());

   // Draw StarLink and its Parts
   else if (objType == "class Starlink")
      drawStarlink(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class StarlinkBody")
      drawStarlinkBody(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class StarlinkArray")
      drawStarlinkArray(obj->getPosition(), obj->getRotation().getRadian());

   // Draw Hubble and its Parts
   else if (objType == "class Hubble")
      drawHubble(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class HubbleTelescope")
      drawHubbleTelescope(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class HubbleComputer")
      drawHubbleComputer(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class HubbleLeft")
      drawHubbleLeft(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class HubbleRight")
      drawHubbleRight(obj->getPosition(), obj->getRotation().getRadian());

   // Draw Dragon and its Parts
   else if (objType == "class Dragon")
      drawCrewDragon(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class DragonCenter")
      drawCrewDragonCenter(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class DragonLeft")
      drawCrewDragonLeft(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class DragonRight")
      drawCrewDragonRight(obj->getPosition(), obj->getRotation().getRadian());

   // Draw GPS and its Parts
   else if (objType == "class GPS")
      drawGPS(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class GPSCenter")
      drawGPSCenter(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class GPSLeft")
      drawGPSLeft(obj->getPosition(), obj->getRotation().getRadian());
   else if (objType == "class GPSRight")
      drawGPSRight(obj->getPosition(), obj->getRotation().getRadian());
   
   // Draw Fragments
   else if (objType == "class Fragment")
      drawFragment(obj->getPosition(), obj->getRotation().getRadian());

   // Error case
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
   // The first step is to cast the void pointer into a game object.
   Simulator* pSim = (Simulator*)p;

   // Pass the Simulator user input
   pSim->getInput(pUI);
 
   // Update all Objects in the Simulation
   pSim->update();

   // Draw every item in the simulator
   vector<Object*> simObjects = pSim->getObjects();
   for (vector<Object*>::iterator it = simObjects.begin(); it != simObjects.end(); it++)
      // Draw the Object based on its class type
      drawObject(*it, pSim->getDebug());
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
   ptUpperRight.setZoom(DEFAULT_ZOOM); /* 128km equals 1 pixel */
   ptUpperRight.setPixelsX(SCREEN_SIZE_X);
   ptUpperRight.setPixelsY(SCREEN_SIZE_Y);
   Interface ui(0, NULL,
      "Orbit Lab",   /* name on the window */
      ptUpperRight);

   // Initialize the Simulator
   Simulator sim = Simulator();

   // set everything into action
   ui.run(callBack, &sim);

   return 0;
}
