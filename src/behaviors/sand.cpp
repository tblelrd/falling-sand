#include "behaviors.h"

namespace SandUtil {
bool can_block_sand(Element type) {
  switch (type) {
  case Element::WATER:
  case Element::EMPTY:
    return false;

  default:
    return true;
  }
}

/**
* returns a status code
*/
int do_movement(Grid& grid, int index) {
  auto [x, y] = grid.position_from(index);
  bool left_first = GetRandomValue(0, 1); // Randomly check left first?
  int offset = left_first ? -1 : 1;
  
  bool will_resist = GetRandomValue(0, 10) < 4;

  if (!can_block_sand(type(x, y + 1))) {
    swap(x, y + 1);
    return 0;
  } else if (!can_block_sand(type(x + offset, y + 1))) {
    swap(x + offset, y + 1);
    return 1;
  } else if (!can_block_sand(type(x - offset, y + 1))) {
    swap(x - offset, y + 1);
    return 1;
  }

  p(x, y)->is_falling = false;
  return 2;
}
}

using namespace SandUtil;
void Behaviors::update_sand(Grid &grid, int index) {
  auto [x, y] = grid.position_from(index);

  Particle& sand = *grid.get_particle(index);
  sand.has_updated = true;
  array<int, 2>& velocity = sand.get_velocity();

  // Check if falling, if not then don't do movement.
  if (!sand.is_falling) {
    velocity[1] = 0;
    if (!can_block_sand(type(x, y + 1))) {
      sand.is_falling = true;
    } else return;
  }

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

  // If it didnt hit a sand block, then increasae velocity, else make it 0.
  if (status <= 1) {
    if (velocity[1] < Behaviors::MAX_GRAVITY) velocity[1]++;
  } else {
    velocity[1] = 1;
  }
}
