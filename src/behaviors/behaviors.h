#ifndef BEHAVIORS_H
#define BEHAVIORS_H

#include "../grid.h"

namespace Behaviors {
  #define type(x, y) grid.get_particle(x, y)->get_type()
  #define p(x, y) grid.get_particle(x, y)
  #define swap(x, y) grid.swap_cells(index, grid.index_from(x, y))

  const int MAX_GRAVITY = 5;

  void update_sand(Grid& grid, int index);
  void update_water(Grid& grid, int index);
  void update_stone(Grid& grid, int index);
}

#endif
