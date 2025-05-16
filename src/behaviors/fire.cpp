#include "behaviors.h"

namespace FireUtil {
bool can_block_fire(Element type) {
  switch (type) {
    case Element::EMPTY:
      return false;

    default: return true;
  }
}
} // namespace FireUtil

using namespace FireUtil;
void Behaviors::update_fire(Grid &grid, int index) {
  auto [x, y] = grid.position_from(index);

  Particle& fire = *grid.get_particle(index);
  fire.has_updated = true;
  
  // Wake up other particles next to it
  Particle& p_left = *grid.get_particle(index - 1);
  Particle& p_right = *grid.get_particle(index + 1);
  p_left.try_fall();
  p_right.try_fall();

  bool left_first = GetRandomValue(0, 1); // Randomly check left first?
  int offset = left_first ? -1 : 1;

  bool vanish = GetRandomValue(0, 30) < 10;
  if (vanish) {
    grid.set_particle(index, Element::EMPTY);
    return;
  }

  if (!can_block_fire(type(x, y - 1)) && GetRandomValue(0, 10) < 5) {
    swap(x, y - 1);
  } else if (!can_block_fire(type(x + offset, y - 1))) {
    swap(x + offset, y - 1);
  } else if (!can_block_fire(type(x - offset, y - 1))) {
    swap(x - offset, y - 1);
  }
}
