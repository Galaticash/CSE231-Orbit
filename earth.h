#pragma once

/*********************************************
 * Earth
 * A planet in the orbital simulator. It has gravity and
 * can be collided with, but can't be destroyed.
 *********************************************/
#include "collisionObject.h"

const double PI = 3.1415926;            // The value of Pi

// TODO: I'm sure there's a better way to calculate framerate
//  (maybe using gl's framerate or something), but this will do for now
const double FPS = 30;          // The number of frames drawn per second     
const double TIME_DILATION = 24 * 60;    // One minute in simulator = One day in real world

// Planet Information
const double SECONDS_DAY = 24 * 60 * 60; // 24 hours * 60 minutes * 60 seconds
const double ROTATION_SPEED = -(2 * PI / FPS) * TIME_DILATION / SECONDS_DAY;

class Earth : public CollisionObject
{
public:
   Earth() : CollisionObject() {
      this->pos = Position(0, 0); 
      this->visual = vector<ColorRect>{};
      createVisual(); // Populate the vector of ColorRects
   };
   
   void update(double time, double gravity = 0.0, double radius = 0.0) { 
      // The Earth will not move, only rotate
      this->angle += ROTATION_SPEED;
   }   

private:
   void createVisual()
   {
      // Translate the previous method into a vector of ColorRects

      // The colors being used for the Earth
      const int* colors[5] =
      {
         RGB_GREY,  // 0
         RGB_BLUE,  // 1
         RGB_GREEN, // 2
         RGB_TAN,   // 3
         RGB_WHITE  // 4
      };

      // All the color points that make up the Earth (1 x 1 Color Rects)
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

      // For every color point that makes up the Earth,
      for (int y = 0; y < 50; y++)
         for (int x = 0; x < 50; x++)
            if (earth[y][x])
            {
               //assert(earth[y][x] > 0 && earth[y][x] <= 4);

               /*
               Position pos;
               pos.setPixelsX(-25.0 * SCALE);
               pos.setPixelsY(-25.0 * SCALE);
               */

               // Note: Earth was easy since position is (0,0)
               // However, seems it is not quite centered
               // Also, instead of rewriting all, could do a typeid() switch case??
               ColorRect rect =
               {
                  static_cast<int>(x * SCALE),
                  static_cast<int>(y * SCALE),

                  static_cast<int>(x * SCALE),
                  static_cast<int>(y * SCALE + SCALE),

                  static_cast<int>(x * SCALE + SCALE),
                  static_cast<int>(y * SCALE + SCALE),

                  static_cast<int>(x * SCALE + SCALE),
                  static_cast<int>(y * SCALE), colors[earth[y][x]] };
               
               // Add the created ColorRect to the Earth's visual
               visual.push_back(rect);
            }
   };
};
