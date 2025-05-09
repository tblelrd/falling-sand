#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include <cstdint>
#include <functional>
#include <utility>

using std::function;
using std::pair;

enum class Element : uint8_t {
  EMPTY,
  WALL, // Wall element which is just the border of the screen.
  SAND,
  WATER,
  STONE,
};

class Particle {
  Element type;
  Color color;

  pair<int, int> velocity;
public:
  Particle(Element type_, std::pair<int, int> velocity_, Color color_);
  Particle(Element type_, Color color_) : Particle(type_, {0, 0}, color_) {}
  Particle(Element type_, std::pair<int, int> velocity_)
      : Particle(type_, velocity_, BLANK) {}
  Particle(Element type_) : Particle(type_, std::make_pair(0, 0)) {}
  Particle() : Particle(Element::EMPTY) {}

  Element get_type() { return type; }
  void set_type(Element type_) { type = type_; }

  Color get_color() { return color; }
  void set_color(Color color_) { color = color_; }

  pair<int, int> get_velocity() { return velocity; }
  void set_velocity(pair<int, int> velocity_) { velocity = velocity_; }

  bool has_updated;
};
#endif
