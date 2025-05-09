#include "main.h"
#include "engine.h"
#include "raylib.h"
#include "grid.h"
#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>

std::array<Element, 3> elements = {
  Element::SAND,
  Element::WATER,
  Element::STONE,
};

void draw_square(int x, int y, int size, Grid& grid, Element type) {
  for (int a = -(size/2); a < (size/2) + 1; a++) {
    for (int b = -(size/2); b < (size/2) + 1; b++) {
      if (grid.get_particle(x + a, y + b)->get_type() != type) {
        grid.set_particle(x + a, y + b, type);
      }
    }
  }
}


void draw_line(
  array<int, 2> pos1,
  array<int, 2> pos2,
  Grid& grid, int size,
  Element type 
) {
  int x1 = pos1[0];
  int y1 = pos1[1];
  int x2 = pos2[0];
  int y2 = pos2[1];

  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);

  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;

  int err = dx - dy;

  while (true) {
    draw_square(x1, y1, size, grid, type);

    if (x1 == x2 && y1 == y2)
      break;

    int e2 = 2 * err;

    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  }
}

int main () {
  int cell_size = 3;
  int width = 300;
  int height = 300;

  int draw_size = 9;

  Grid grid = Grid(width, height);
  Engine engine = Engine(grid);

  InitWindow(cell_size * width, cell_size * height, "Falling In Sand");
  SetTargetFPS(60);

  Element selected_element = elements[0];

  int prev_x = 0;
  int prev_y = 0;
  while (!WindowShouldClose()) {

    engine.post_step();
    engine.step();

    int keyPressed = GetCharPressed();
    if (keyPressed > '0' && keyPressed < '9') {
      int index = keyPressed - 49;
      printf("%d\n", index);
      if (index < 0 || index > elements.size()) {
      }
      else {
        selected_element = elements[index];
      }
    }

    bool left_mouse = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    bool right_mouse = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    Vector2 mouse = GetMousePosition();
    int x = mouse.x / cell_size;
    int y = mouse.y / cell_size;
    if (left_mouse || right_mouse) {
      draw_line(
        {prev_x, prev_y},
        {x, y},
        grid, draw_size,
        right_mouse ? Element::EMPTY : selected_element
      );

    }
    prev_x = x;
    prev_y = y;

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        Particle& particle = *grid.get_particle(x, y);
        Element type = particle.get_type();
        Color color = particle.get_color();
        DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, color);
        // if (particle.should_update()) DrawRectangleLines(x * cell_size, y * cell_size, cell_size, cell_size, RED);
      }
    }
    EndDrawing();
  }
  return 0;
}
