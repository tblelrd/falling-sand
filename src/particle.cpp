#include "particle.h"
#include "raylib.h"
#include <algorithm>

// Color
int get_element_variance(Element type) {
  switch (type) {
    case Element::SAND:
    case Element::STONE:
    case Element::WOOD:
    case Element::FIRE:
    case Element::EMBER:
      return 10;

    case Element::WATER:
      return 1;

    default: return 0;
  }
}

// Powders
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

Color redden (Color color, float scalar) {
  using std::clamp;
  float t = clamp(scalar / 10.0f, 0.0f, 1.0f);

  int r = (int) (color.r + (255 - color.r) * t);
  int g = (int) (color.g * (1 - t));
  int b = (int) (color.b * (1 - t));

  Color result;
  result.r = r;
  result.g = g;
  result.b = b;
  result.a = color.a;

  return result;
}

Color Particle::get_color() {
  // if (heat_factor > 0) {
  //   return redden(color, heat_factor);
  // }
  return color;
}

void Particle::try_fall() {
  float random = GetRandomValue(0, 100) / 100.0;
  if (random > get_element_resistance(type)) is_falling = true;
}
