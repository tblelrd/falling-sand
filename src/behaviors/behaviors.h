#ifndef BEHAVIORS_H
#define BEHAVIORS_H

#include "../grid.h"

namespace Behaviors {
  void update_sand(Grid& grid, int index);
  void update_water(Grid& grid, int index);
  void update_stone(Grid& grid, int index);
}

#endif
