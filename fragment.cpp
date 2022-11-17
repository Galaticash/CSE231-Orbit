#include "fragment.h"
#include "simulator.h"

void Fragment::breakApart(Simulator* sim) {
   sim->removeCollider(this); // Remove pointer to self
   delete this; // Delete self
};