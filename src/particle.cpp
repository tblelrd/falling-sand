#include "particle.h"
#include "raylib.h"

int get_element_variance(Element type) {
  switch (type) {
    case Element::SAND:
    case Element::STONE:
      return 10;

    case Element::WATER:
      return 1;

    default: return 0;
  }
}

float get_element_resistance(Element type) {
  switch (type) {
    case Element::SAND:
      return 0.5;

    default: return 0;
  }
}

Particle::Particle(Element type_, array<int, 2> velocity_, Color color_) {
  type = type_;
  velocity = velocity_;
  color = color_;
}

void Particle::try_fall() {
  float random = GetRandomValue(0, 100) / 100.0;
  if (random > get_element_resistance(type)) is_falling = true;
}
