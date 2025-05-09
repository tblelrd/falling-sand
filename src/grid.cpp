#include "grid.h"
#include "colors.h"

Grid::Grid(int width_, int height_) {
  width = width_;
  height = height_;
  cells = nullptr;

  reset_grid();
}

void Grid::reset_grid() {
  delete cells; // Free the memory.
  // cells = new Particle[width * height];
  cells = new Particle*[width * height];
  for (int i = 0; i < width * height; i++) {
    cells[i] = new Particle();
  }
}

pair<int, int> Grid::position_from(int index) {
  if (out_of_bounds(index)) return { -1, -1 };

  return {
    index % width,
    index / width,
  };
}

int Grid::index_from(int x, int y) {
  if (out_of_bounds(x, y)) return -1;

  return (y * width) + x;
}

Particle* Grid::get_particle(int index) {
  if (out_of_bounds(index)) return &wall;
  return cells[index];
}

Particle* Grid::get_particle(int x, int y){
  if (out_of_bounds(x, y)) return &wall;
  return Grid::get_particle(index_from(x, y));
}

bool Grid::set_particle(int index, Particle particle) {
  if (out_of_bounds(index)) return false;

  delete cells[index]; // Delete if exists
  cells[index] = new Particle(particle); // Allocate on the heap so it doesn't disappear.
  return true;
}

bool Grid::set_particle(int x, int y, Particle particle) {
  if (out_of_bounds(x, y)) return false;

  return Grid::set_particle(
    Grid::index_from(x, y),
    particle
  );
}

Color color_from_element(Element type, unordered_map<Element, Color> color_map) {
  Color color = color_map.at(type);
  if (type == Element::EMPTY) return color;
  
  ColorHSL hsl = rgb_to_hsl(color);
  // printf("%f, %f, %f\n", hsl.h, hsl.s, hsl.l);
  int variance = get_element_variance(type);
  hsl.l += GetRandomValue(-variance, variance) * 0.01;
  if (hsl.l < 0) hsl.l = 0;
  else if (hsl.l > 1) hsl.l = 1;

  color = hsl_to_rgb(hsl);

  return color;
}

bool Grid::set_particle(int index, Element type) {
  Particle particle = Particle(type, color_from_element(type, Grid::color_map));

  return Grid::set_particle(index, particle);
}

bool Grid::set_particle(int x, int y, Element type) {
  return Grid::set_particle(
    Grid::index_from(x, y),
    type
  );
}

bool Grid::swap_cells(int f_index, int t_index) {
  if (out_of_bounds(f_index) || out_of_bounds(t_index)) return false;

  Particle* temp_cell = get_particle(f_index);
  cells[f_index] = cells[t_index];
  cells[t_index] = temp_cell;
  return true;
}
