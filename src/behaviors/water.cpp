#include "behaviors.h"
#include <cassert>

namespace WaterUtil {
const int DISPERSION = 4; 

bool can_block_water(Element type) {
  switch (type) {
    case Element::EMPTY:
      return false;

    default:
      return true;
    }
}

bool can_block_dispersion(Element type) {
  switch (type) {
    case Element::EMPTY:
    case Element::WATER:
      return false;

    default:
      return true;
  }
}


void do_dispersion(Grid& grid, int index, int offset) {
  auto [x, y] = grid.position_from(index);

  Particle& water = *grid.get_particle(index);
  array<int, 2>& velocity = water.get_velocity();

  if (velocity[0] == 0) velocity[0] = offset;

  int free_spaces = 0;
  for (int i = 1; i <= DISPERSION; i++) {
    if (!can_block_dispersion(type(x + (velocity[0] * i), y))) {
      free_spaces ++;
    } else break;
  }

  // Do a bounce back.
  if (free_spaces != DISPERSION) free_spaces -= GetRandomValue(0, free_spaces);

  if (free_spaces > 0 && !can_block_water(type(x + velocity[0] * free_spaces, y))) {
    bool success = swap(x + velocity[0] * free_spaces, y);
  } else {
    velocity[0] *= -1;
  }
}

/**
* Returns a status code.
*/
int do_movement(Grid& grid, int index) {
  auto [x, y] = grid.position_from(index);
  bool left_first = GetRandomValue(0, 1); // Randomly pick side
  int offset = left_first ? -1 : 1;
  
  bool will_resist = GetRandomValue(0, 10) < 4;

  if (!can_block_water(type(x, y + 1))) {
    swap(x, y + 1);
    return 0;
  } else if (!can_block_water(type(x + offset, y + 1))) {
    swap(x + offset, y + 1);
    return 1;
  } else if (!can_block_water(type(x - offset, y + 1))) {
    swap(x - offset, y + 1);
    return 1;
  } else {
    do_dispersion(grid, index, offset);
  }
  return 2;
}
}

using namespace WaterUtil;
void Behaviors::update_water(Grid &grid, int index) {
  auto [x, y] = grid.position_from(index);

  Particle& water = *grid.get_particle(index);
  water.has_updated = true;
  array<int, 2>& velocity = water.get_velocity();

  // Wake up other particles next to it
  Particle& p_left = *grid.get_particle(index - 1);
  Particle& p_right = *grid.get_particle(index + 1);
  p_left.try_fall();
  p_right.try_fall();

  int status = 0;
  for (int i = 0; i < velocity[1]; i++) {
    auto [px, py] = grid.position_from(index);
    int new_index = grid.index_from(px, py + i);

    status = do_movement(grid, new_index);
    if (status > 0) break;
  }

  // If it didnt hit a sand block, then increase velocity, else make it 1.
  if (status <= 1) {
    if (velocity[1] < Behaviors::MAX_GRAVITY) velocity[1]++;
  } else {
    velocity[1] = 1;
  }
}
