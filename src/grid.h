#ifndef GRID_H
#define GRID_H

#include "particle.h"
#include <utility>
#include <unordered_map>

using std::unordered_map;
using std::pair;

Color make_transparent(Color color);
class Grid {
  Particle** cells;

  unordered_map<Element, Color> color_map = {
    {Element::EMPTY, BLANK},
    {Element::WALL, BLANK},
    {Element::SAND, GOLD},
    {Element::WATER, {0, 82, 172, 150}},
    {Element::STONE, DARKGRAY},
    {Element::WOOD, BROWN},
    {Element::EMBER, {232, 198, 88, 255}},
    {Element::FIRE, {232, 158, 88, 255}}
  };

  Particle wall = Particle(Element::WALL); // Particle representing the wall.
  int width;
  int height;

  bool out_of_bounds(int index) { return index < 0 || index >= width * height; }
  bool out_of_bounds(int x, int y) {
    if (x < 0 || x >= width) return true;
    if (y < 0 || y >= height) return true;
    return false;
  }

public:
  Grid(int width_, int height_);

  void reset_grid();

  /**
   * Will return -1 or {-1, -1}
   * if provided index or position is
   * out of bounds.
   */
  pair<int, int> position_from(int index);
  int index_from(int x, int y);

  /**
  * These methods will return a wall particle
  * if the position/index is out of bounds.
  */
  Particle* get_particle(int index);
  Particle* get_particle(int x, int y);

  /**
  * These methods will return true if success,
  * false if fail.
  */
  bool set_particle(int index, Particle particle);
  bool set_particle(int x, int y, Particle particle);
  bool set_particle(int index, Element type);
  bool set_particle(int x, int y, Element type);

  bool swap_cells(int index_from, int index_to);

  int get_width() { return width; }
  int get_height() { return height; }
};

#endif
