#pragma once

/*********************************************
 * Earth
 * A planet in the orbital simulator. It has gravity and
 * can be collided with, but can't be destroyed.
 *********************************************/
#include "collisionObject.h"

class Earth : public CollisionObject
{
public:
   Earth() : CollisionObject() { this->pos = Position(0, 0); };

private:

};
