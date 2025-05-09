#ifndef ENGINE_H
#define ENGINE_H

#include "grid.h"

class Engine {
  Grid grid;
public:
  /*
  * This syntax is because grid has no default constructor,
  * so the grid must be explicitly defined before the
  * constructor (the constructor default constructs everything
  * before any code inside of it runs).
  */
  Engine(Grid grid_) : grid(grid_) {}

  void step();
  void post_step();
};

#endif
