#include "engine.h"
#include "behaviors/behaviors.h"

void do_update (Grid& grid, Particle& particle, int index) {
  Element type = particle.get_type();

  switch (type) {
    case Element::SAND:
      Behaviors::update_sand(grid, index);
      break; 

    case Element::WATER:
      Behaviors::update_water(grid, index);
      break;

    case Element::STONE:
      Behaviors::update_stone(grid, index);
      break;

    case Element::EMPTY:
    default: break;
  }

  particle.has_updated = true;
}

void Engine::step() {
  int height = grid.get_height();
  int width = grid.get_width();

  for (int y = height - 1; y >= 0; y--) {
    for (int x = 0; x < width; x++) {
      int scanx = y % 2 == 0
        ? x
        : width - (x + 1);

      Particle &particle = *grid.get_particle(scanx, y);
      if (particle.has_updated) continue;
      do_update(grid, particle, grid.index_from(scanx, y));
    }
  }
}

void Engine::post_step() {
  int height = grid.get_height();
  int width = grid.get_width();

  for (int y = height - 1; y >= 0; y--) {
    for (int x = 0; x < width; x++) {
      grid.get_particle(x, y)->has_updated = false;
    }
  }
}
