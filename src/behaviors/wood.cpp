#include "behaviors.h"
#include <cstdio>

namespace WoodUtil {
bool is_fire(Element type) {
  switch (type) {
    case Element::FIRE:
    case Element::EMBER:
      return true;

    default: return false;
  }
}

} // namspace WoodUtil

using namespace WoodUtil;
void Behaviors::update_wood(Grid &grid, int index) {
  auto [x, y] = grid.position_from(index);

  int fire_counter = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (is_fire(type(x + (i - 1), y + (j - 1)))) {
        fire_counter ++;
      }
    }
  }

  bool start_burning = GetRandomValue(1, 40) < fire_counter;

  if (start_burning) {
    grid.set_particle(index, Element::EMBER);
  }
}
