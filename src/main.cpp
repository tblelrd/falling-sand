#include "main.h"
#include "raylib.h"
#include "grid.h"

int main () {
  int cell_size = 10;
  int width = 50;
  int height = 50;
  Grid grid = Grid(width, height);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      grid.set_particle(x, y, Element::SAND);
    }
  }

  InitWindow(cell_size * width, cell_size * height, "Falling In Sand");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        Color color = grid.get_particle(x, y)->get_color();
        DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, color);
      }
    }
    EndDrawing();
  }
  return 0;
}
