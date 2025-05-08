#ifndef GRID_H
#define GRID_H

#include "particle.h"
#include <utility>
#include <unordered_map>

using std::unordered_map;
using std::pair;

class Grid {
  Particle* cells;

  unordered_map<Element, Color> color_map = {
    {Element::EMPTY, BLANK},
    {Element::SAND, ORANGE},
    {Element::WATER, SKYBLUE},
    {Element::STONE, GRAY},
  };

  int width;
  int height;
public:
  Grid(int width_, int height_);

  void reset_grid();

  pair<int, int> position_from(int index);
  int index_from(int x, int y);

  Particle* get_particle(int index);
  Particle* get_particle(int x, int y);
  bool set_particle(int index, Particle particle);
  bool set_particle(int index, Element type);

  void swap_cells(int index_from, int index_to);
};

#endif
