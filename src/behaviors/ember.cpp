#include "behaviors.h"

namespace EmberUtil {
bool is_empty (Element type) { return type == Element::EMPTY; }
} // namespace EmberUtil

using namespace EmberUtil;
void Behaviors::update_ember(Grid &grid, int index) {
  auto [x, y] = grid.position_from(index);

  Particle& ember = *grid.get_particle(index);
  ember.has_updated = true;

  bool blaze = GetRandomValue(1, 250) == 1;
  if (blaze) {
    grid.set_particle(index, Element::FIRE);
    return;
  }

  bool left_first = GetRandomValue(0, 1);
  int offset = left_first ? -1 : 1;

  bool flame = GetRandomValue(1, 5) == 1;
  if (!flame) return;
  if (is_empty(type(x, y - 1))) {
    grid.set_particle(x, y - 1, Element::FIRE);
  } else if (is_empty(type(x + offset, y - 1))) {
    grid.set_particle(x + offset, y - 1, Element::FIRE);
  } else if (is_empty(type(x - offset, y - 1))) {
    grid.set_particle(x - offset, y - 1, Element::FIRE);
  } else if (is_empty(type(x + offset, y))) {
    grid.set_particle(x + offset, y, Element::FIRE);
  } else if (is_empty(type(x - offset, y))) {
    grid.set_particle(x - offset, y, Element::FIRE);
  }
}
