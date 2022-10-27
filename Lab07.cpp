/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cmath>
#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POINT
using namespace std;

const double GRAVITY = -9.8067;           // m/s^2
const double EARTH_RADIUS = 6378000.0;    // meters
const double TIME = 48;                   // seconds

/*************************************************************************
 * GRAVITY DIRECTION
 * Calculates the angle at which an object is pulled by gravity.
 * Fromula: d = atan( xe - xs, ye - ys )
 * d = direction of the pull of gravity      (radians)
 * xe = horizontal position of the center of the earth : 0m
 * ye = vertical position of the center of the earth : 0m
 * xs = horizontal position of the satellite (meters)
 * ys = vertical position of the satellite   (meters)
 *************************************************************************/
double gravityDirection(double xs, double ys) {
   double d = atan2( ys, xs);
   return d;
}

/*************************************************************************
 * HEIGHT ABOVE EARTH
 * Finds the height above the earth an object is.
 * Formula: h = sqrt(x * x + y * y) - r
 * h = distance between the surface of the earth and the object (meters)
 * x = horizontal position of object   (meters)
 * y = vertical position of object     (meters)
 * r = radius of earth                 (meters)
 *************************************************************************/
double heightAboveEarth(double x, double y) {
   double h = sqrt(x * x + y * y) - EARTH_RADIUS;
   return h;
}

/*************************************************************************
 * GRAVITY EQUATION
 * This calculates the total acceleration due to earth's gravity
 * Formula: g * ( r / ( r + h ) ) ^ 2 = gh
 * gh = magnitude of acceleration due to gravity at altitude h (m/s^2)
 * g  = gravity at sea level   (m/s^2)
 * r  = radius of earth        (meters)
 * h  = height above earth     (meters)
 *************************************************************************/
double gravityEquation(double h) {
   // TODO: Figure out if it is better to repeat this equation or to use the square function
   double gh = GRAVITY * pow(( EARTH_RADIUS / ( EARTH_RADIUS + h ) ), 2);
   return gh;
}

/*************************************************************************
 * HORIZONTAL ACCELERATION
 * ddx = a * sin( angle )
 * ddx = horizontal component of acceleration      (m/s^2)
 * a = total acceleration                          (m/s^2)
 * angle = angle of the direction of acceleration  (0 degrees is up)
 *************************************************************************/
double horizontalAcceleration(double a, double angle) {
   double ddx = a * sin( angle );
   return ddx;
}

/*************************************************************************
 * VERTICAL ACCELERATION
 * ddy = a * cos( angle )
 * ddy = vertical component of acceleration        (m/s^2)
 * a = total acceleration                          (m/s^2)
 * angle = angle of the direction of acceleration  (0 degrees is up)
 *************************************************************************/
double verticalAcceleration(double a, double angle) {
   double ddy = a * cos( angle );
   return ddy;
}

/*************************************************************************
 * DISTANCE FORMULA
 * This formula is used for calculating the distance something travelled.
 * Can be used for both vertical and horizontal distance.
 * Formula: s = so + (v * t) + (.5 * a * t * t)
 *     ex. (x = xo + (dx * t) + (.5 * ddx * t * t))
 * s = distance            (meters)
 * so = initial distance   (meters)
 * v = velocity            (m/s)
 * t = time                (seconds)
 * a = acceleration        (m/s^2)
 *************************************************************************/
double distanceFormula(double so, double v, double a) {
   double s = so + (v * TIME) + (.5 * a * TIME * TIME);
   return s;
}

/*************************************************************************
 * POSITION CONSTANT VELOCITY
 * Compute the distance when given a constant velocity.
 * Can be used for both horizontal and vertical distance.
 * Formula: s = so + v * t
 *     ex. (x = xo + dx * t)
 * s  = distance           (meters)
 * so = initial position   (meters)
 * v  = velocity           (m/s)
 * t  = time               (seconds)
 *************************************************************************/
double verticalConstantVelocity(double so, double v) {
   double s = so + v * TIME;
   return s;
}

/*************************************************************************
 * VELOCITY CONSTANT ACCELERATION
 * Compute the velocity when given a constant acceleration. 
 * Can be used for both horizontal and vertical velocity.
 * Formula: v = vo + a * t
 *    ex. (dx = dxo + ddx * t)
 * v = velocity            (m/s)
 * vo = initial velocity   (m/s)
 * a = acceleration        (m/s^2)
 * t = time                (seconds)
 *************************************************************************/
double velocityConstantAcceleration(double vo, double a) {
   double v = vo + a * TIME;
   return v;
}

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) :
      ptUpperRight(ptUpperRight)
   {
      /*
      ptHubble.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptHubble.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptStarlink.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptStarlink.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptCrewDragon.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptCrewDragon.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptShip.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptShip.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
      */
      //ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      //ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      // Set a satellite directly above the earth in position for GEO orbit.
      ptGPS.setMeters(0.0, 42164000.0);
      double angle = gravityDirection(ptGPS.getMetersX(), ptGPS.getMetersY());
      double height = heightAboveEarth(ptGPS.getMetersX(), ptGPS.getMetersY());
      double totalAcc = gravityEquation(height);
      double vAcc = verticalAcceleration(totalAcc, angle);
      double hAcc = horizontalAcceleration(totalAcc, angle);

      // Velocity required to remain in GEO orbit: -3,100.0 m/s 
      // The sign is to match earths rotation direction when starting directly above it



      //ptSputnik.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      //ptSputnik.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      angleShip = 0.0;
      angleEarth = 0.0;
      phaseStar = 0;
   }

   Position ptHubble;
   Position ptSputnik;
   Position ptStarlink;
   Position ptCrewDragon;
   Position ptShip;
   Position ptGPS;
   Position ptStar;
   Position ptUpperRight;

   unsigned char phaseStar;

   double angleShip;
   double angleEarth;
};

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
   Demo* pDemo = (Demo*)p;

   //
   // accept input
   //

   // move by a little
   if (pUI->isUp())
      pDemo->ptShip.addPixelsY(1.0);
   if (pUI->isDown())
      pDemo->ptShip.addPixelsY(-1.0);
   if (pUI->isLeft())
      pDemo->ptShip.addPixelsX(-1.0);
   if (pUI->isRight())
      pDemo->ptShip.addPixelsX(1.0);


   //
   // perform all the game logic
   //

   // rotate the earth
   pDemo->angleEarth += 0.01;
   //pDemo->angleShip += 0.02;
   pDemo->phaseStar++;

   // GOAL: Get an item to orbit the Earth
 
   // seconds between each update (Find a way not to hard-code)
   int dTime = 48;
   
   // The velocity of the item
   // Use gravity equation and others so it orbits instead of having const velocity
   double velocity = -3100.0;
   // TODO: Velocity x/y should differ based on current position/gravity pull so it can maintain orbit

   // Adjust the position given the velocity and time
   double xGPS = pDemo->ptGPS.getMetersX() + (velocity * dTime);
   double yGPS = pDemo->ptGPS.getMetersY() + (velocity * dTime);

   // Update the GPS's current position
   pDemo->ptGPS = Position(xGPS, yGPS);
   

   //
   // draw everything
   //

   Position pt;

   // draw satellites
   //drawCrewDragon(pDemo->ptCrewDragon, pDemo->angleShip);
   //drawHubble    (pDemo->ptHubble,     pDemo->angleShip);
   //drawSputnik   (pDemo->ptSputnik,    pDemo->angleShip);
   //drawStarlink  (pDemo->ptStarlink,   pDemo->angleShip);
   //drawShip      (pDemo->ptShip,       pDemo->angleShip, pUI->isSpace());
   drawGPS       (pDemo->ptGPS,        pDemo->angleShip);
   /*
   // draw parts
   pt.setPixelsX(pDemo->ptCrewDragon.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptCrewDragon.getPixelsY() + 20);
   drawCrewDragonRight(pt, pDemo->angleShip); // notice only two parameters are set
   pt.setPixelsX(pDemo->ptHubble.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptHubble.getPixelsY() + 20);
   drawHubbleLeft(pt, pDemo->angleShip);      // notice only two parameters are set
   pt.setPixelsX(pDemo->ptGPS.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptGPS.getPixelsY() + 20);
   drawGPSCenter(pt, pDemo->angleShip);       // notice only two parameters are set
   pt.setPixelsX(pDemo->ptStarlink.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptStarlink.getPixelsY() + 20);
   drawStarlinkArray(pt, pDemo->angleShip);   // notice only two parameters are set
   
   // draw fragments
   pt.setPixelsX(pDemo->ptSputnik.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptSputnik.getPixelsY() + 20);
   drawFragment(pt, pDemo->angleShip);
   pt.setPixelsX(pDemo->ptShip.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptShip.getPixelsY() + 20);
   drawFragment(pt, pDemo->angleShip);
   */
   // draw a single star
   drawStar(pDemo->ptStar, pDemo->phaseStar);

   // draw the earth
   pt.setMeters(0.0, 0.0);
   drawEarth(pt, pDemo->angleEarth);
}

double Position::metersFromPixels = 40.0;

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
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}
