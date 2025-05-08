#ifndef GRID_H
#define GRID_H

#include "particle.h"
#include <utility>

using std::pair;

class Grid {
  Particle* cells;

  int width;
  int height;
public:
  Grid(int width_, int height_);

  void reset_grid();

  pair<int, int> position_from(int index);
  int index_from(int x, int y);

  Particle* get_particle(int index);
  Particle* get_particle(int x, int y);

  void swap_cells(int index_from, int index_to);
};

#endif
