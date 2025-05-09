#include "main.h"
#include "engine.h"
#include "raylib.h"
#include "grid.h"
#include <array>
#include <cstdio>

std::array<Element, 3> elements = {
  Element::SAND,
  Element::WATER,
  Element::STONE,
};

int main () {
  int cell_size = 4;
  int width = 250;
  int height = 250;

  int draw_size = 9;

  Grid grid = Grid(width, height);
  Engine engine = Engine(grid);

  InitWindow(cell_size * width, cell_size * height, "Falling In Sand");
  SetTargetFPS(60);

  Element selected_element = elements[0];

  while (!WindowShouldClose()) {

    engine.step();
    engine.post_step();

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
    // else if (keyPressed == ' ') {
    //   engine.step();
    //   engine.post_step();
    //
    // }

    bool left_mouse = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    bool right_mouse = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    if (left_mouse || right_mouse) {
      Vector2 mouse = GetMousePosition();
      int x = mouse.x / cell_size;
      int y = mouse.y / cell_size;
      // if (right_mouse) {
      //   grid.set_particle(x, y, Element::EMPTY);
      //   continue;
      // }
      // if (grid.get_particle(x, y)->get_type() != selected_element) {
      //   grid.set_particle(x, y, selected_element);
      // }

      for (int i = -(draw_size/2); i < (draw_size/2) + 1; i++) {
        for (int j = -(draw_size/2); j < (draw_size/2) + 1; j++) {
          if (right_mouse) {
            grid.set_particle(x + i, y + j, Element::EMPTY);
            continue;
          }
          if (grid.get_particle(x + i, y + j)->get_type() != selected_element) {
            grid.set_particle(x + i, y + j, selected_element);
          }
        }
      }
    }

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        Element type = grid.get_particle(x, y)->get_type();
        Color color = grid.get_particle(x, y)->get_color();
        DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, color);
      }
    }
    EndDrawing();
  }
  return 0;
}
