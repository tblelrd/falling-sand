#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include <cstdint>
#include <functional>
#include <unordered_map>

using std::array;
using std::function;
using std::unordered_map;

enum class Element : uint8_t {
  EMPTY,
  WALL, // Wall element which is just the border of the screen.
  SAND,
  WATER,
  STONE,
};

// How resistant it is to change.
float get_element_resistance(Element type);

// To get the variance in the color of the element.
int get_element_variance(Element type);

class Particle {
  Element type;
  Color color;

  array<int, 2> velocity;
public:
  Particle(Element type_, array<int, 2> velocity_, Color color_);
  Particle(Element type_, Color color_) : Particle(type_, {0, 0}, color_) {}
  Particle(Element type_) : Particle(type_, BLANK) {}
  Particle() : Particle(Element::EMPTY) {}

  Element get_type() { return type; }
  void set_type(Element type_) { type = type_; }

  Color get_color() { return color; }
  void set_color(Color color_) { color = color_; }

  array<int, 2>& get_velocity() { return velocity; }
  void set_velocity(array<int, 2> velocity_) { velocity = velocity_; }

  /**
  * Should only be run when something
  * touches this particle, not when empty space
  * below.
  */
  void try_fall();

  bool has_updated;
  bool is_falling = true;
};
#endif
