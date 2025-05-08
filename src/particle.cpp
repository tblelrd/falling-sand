#include "particle.h"
#include "colors.h"
#include "raylib.h"
#include <unordered_map>

using std::unordered_map;
using std::pair;

unordered_map<Element, Color> color_map = {
  {Element::EMPTY, LIGHTGRAY},
  {Element::SAND, YELLOW},
  {Element::SAND, SKYBLUE},
  {Element::STONE, GRAY},
};


Color color_from_element(Element type) {
  Color color = color_map.at(type);
  
  ColorHSL hsl = rgb_to_hsl(color);
  hsl.l += GetRandomValue(-5, 5) * 0.1;

  color = hsl_to_rgb(hsl);

  return color;
}

Particle::Particle(Element type_, pair<int, int> velocity_) {
  type=type_;
  velocity=velocity_;
  color=color_from_element(type_);
}
