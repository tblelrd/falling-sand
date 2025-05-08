#include "grid.h"
#include <exception>

Grid::Grid(int width_, int height_) {
  width = width_;
  height = height_;

  reset_grid();
}

void Grid::reset_grid() {
  cells = new Particle[width * height];
}

pair<int, int> Grid::position_from(int index) {
  if (index > width * height) throw std::exception();

  return {
    index % width,
    index / width,
  };
}

int Grid::index_from(int x, int y) {
  
}
