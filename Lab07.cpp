/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was realizing atan2()'s parameters are labelled incorrectly.
 *       In fact, it's the only math item that is ordered 'Y, X' instead of 'X, Y'.
 *       Another hard part was realizing
 * 5. How long did it take for you to complete the assignment?
 *      4 hours
 *****************************************************************/

#include <cmath>
#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POINT
using namespace std;

// Gravity constant
const double GRAVITY = -9.8067;           // m/s^2
const double PI = 3.1415926;            // The value of Pi

// Simulation Information
// TODO: I'm sure there's a better way to calculate this
//  (maybe using gl's framerate or something), but this will do for now
const double FPS = 30;          // The number of frames drawn per second          
const double TIME = 48;         // Real-world seconds between frames
const double TIME_DILATION = 24 * 60;    // One minute in simulator = One day in real world

// Planet Information
const double EARTH_RADIUS = 6378000.0;    // meters
const double SECONDS_DAY = 24 * 60 * 60; // 24 hours * 60 minutes * 60 seconds
const double ROTATION_SPEED = -(2 * PI / FPS) * TIME_DILATION / SECONDS_DAY;

// Constants for GEO Orbit
const double GEO_HEIGHT = 35786000.0 + EARTH_RADIUS; // GEO orbit, items here should match Earth's rotation
const double GEO_VELOCITY_X = -3100.0;  // moving 3.1 km/s (to the left in this example)

// To show goal orbit and distance from Earth
// Better to leave as a bool, or comment out?
const bool SHOW_TESTING_VISUALS = false;

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
    double d = atan2(xs, ys);
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
        // Comment out all other items 
        /*
        ptHubble.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptHubble.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        ptStarlink.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptStarlink.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        ptCrewDragon.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptCrewDragon.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        ptShip.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptShip.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        //ptSputnik.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        //ptSputnik.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        // Creates a star at a random position
        /*ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
        */
        //ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        //ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        initializeGPS();

        angleShip = 0.0;
        angleEarth = 0.0;
        phaseStar = 0;
    }

    /************************************************************
     * INITIALIZE GPS
     * Create a GPS object in GEO orbit
     ************************************************************/
    void initializeGPS()
    {
        // Set a satellite directly above the earth in position for GEO orbit.
        ptGPS.setMeters(0.0, GEO_HEIGHT);

        /*
        * Moved to callback,
        * TODO: Would be good to calculate here, but as member variables, or a method?
        *
        double angle = gravityDirection(ptGPS.getMetersX(), ptGPS.getMetersY());
        double height = heightAboveEarth(ptGPS.getMetersX(), ptGPS.getMetersY());
        double totalAcc = gravityEquation(height);
        double vAcc = verticalAcceleration(totalAcc, angle);
        double hAcc = horizontalAcceleration(totalAcc, angle);
        */

        // Velocity required to remain in GEO orbit: -3,100.0 m/s
        // The sign is to match earths rotation direction when starting directly above it
        ptGPSVelocityX = GEO_VELOCITY_X;
        ptGPSVelocityY = 0;
    }

    /************************************************************
    * UPDATE GPS POSITION
    * Update the GPS's current position and velocity by calculating
    *  its angle, height, and acceleration through various equations
    ************************************************************/
    void updateGPSPosition()
    {
        // TODO: This method will later be moved to object classes.
        //  Can then update each specific object's values

        // Calculates the current angle and distance from the Earth (0, 0)
        double angle = gravityDirection(this->ptGPS.getMetersX(), this->ptGPS.getMetersY());
        double height = heightAboveEarth(this->ptGPS.getMetersX(), this->ptGPS.getMetersY());

        // Calculate the current acceleration
        double totalAcc = gravityEquation(height);
        double vAcc = verticalAcceleration(totalAcc, angle);
        double hAcc = horizontalAcceleration(totalAcc, angle);

        // Update the current velocity with the current acceleration
        this->ptGPSVelocityX = velocityConstantAcceleration(this->ptGPSVelocityX, hAcc);
        this->ptGPSVelocityY = velocityConstantAcceleration(this->ptGPSVelocityY, vAcc);

        // Adjust the position given the current position, velocity, and acceleration
        double xGPS = distanceFormula(this->ptGPS.getMetersX(), this->ptGPSVelocityX, hAcc);
        double yGPS = distanceFormula(this->ptGPS.getMetersY(), this->ptGPSVelocityY, vAcc);

        // Update the GPS's current position
        this->ptGPS = Position(xGPS, yGPS);
    }

   Position ptHubble;
   Position ptSputnik;
   Position ptStarlink;
   Position ptCrewDragon;
   Position ptShip;
   Position ptGPS;  // TODO: Make each item an object of it's own, with a position, velocity, etc
   Position ptStar;
   Position ptUpperRight;

   unsigned char phaseStar;

   double angleShip;
   double angleEarth;

   double ptGPSVelocityX;
   double ptGPSVelocityY;
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
   pDemo->angleEarth += ROTATION_SPEED;
   //pDemo->angleShip += 0.02;
   pDemo->phaseStar++;

   // GOAL: Get an item to orbit the Earth
   
   if (SHOW_TESTING_VISUALS)
   {
       // Draw an approximate orbit in red (starting height of GPS -> convert to pixels)
       drawCircle(Position(0.0, 0.0), GEO_HEIGHT * (50 / EARTH_RADIUS));
   }

   // Update the GPS's position
   pDemo->updateGPSPosition();

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

   // draw a single star
   drawStar(pDemo->ptStar, pDemo->phaseStar);
   */

   if (SHOW_TESTING_VISUALS)
   {
       // Draw a line between the Earth and ptGPS
       drawLine(Position(0.0, 0.0), pDemo->ptGPS);
   }

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
