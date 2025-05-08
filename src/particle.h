#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include <cstdint>
#include <utility>

enum class Element : uint8_t {
  EMPTY,
  SAND,
  WATER,
  STONE,
};

class Particle {
  Element type;
  Color color;

  std::pair<int, int> velocity;

  bool has_updated;

public:
  Particle(Element type_, std::pair<int, int> velocity_);
  Particle(Element type_) : Particle(type_, {0, 0}) {}
  Particle() : Particle(Element::EMPTY) {}
};
#endif
