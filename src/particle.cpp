#include "particle.h"
#include "raylib.h"

using std::pair;

Particle::Particle(Element type_, pair<int, int> velocity_, Color color_) {
  type=type_;
  velocity=velocity_;
  color=color_;
}
