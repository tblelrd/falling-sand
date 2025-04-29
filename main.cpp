#include "raylib.h"
#include <cstdint>
#include <cstdio>
#include <unordered_map>

// --- DEFINITIONS ---
#define u8 uint8_t
// Particles
#define id_empty (u8) 0
#define id_sand (u8) 1
#define id_water (u8) 2

// --- GLOBALS ---
const int CELL_SIZE = 10;
const int GRID_WIDTH = 80;
const int GRID_HEIGHT = 60;

std::unordered_map<u8, Color> color_map = {
    {id_empty, LIGHTGRAY}, // AIR
    {id_sand, YELLOW},    // SAND
    {id_water, SKYBLUE}    // WATER??
};

int grid[GRID_WIDTH * GRID_HEIGHT] = {0};


// --- STRUCTS ---
struct Particle {
  u8 id;
  Vector2 velocity;
  Color color;
  Particle(u8 id, Vector2 velocity) {
    id=id;
    velocity=velocity;
    color=color_map.at(id);
  }
};

// --- FUNCTIONS ---
bool can_block_sand(int cell_type) {
  if (cell_type == id_sand) return true; // SAND
  return false;
}

bool can_block_water(int cell_type) {
  if (cell_type > 0) return true;
  return false;
}

int get_index_at(int x, int y) {
  // Clamp x and y within bounds.
  if (x >= GRID_WIDTH) x = GRID_WIDTH - 1;
  else if (x < 0) x = 0;
  if (y >= GRID_HEIGHT) y = GRID_HEIGHT;
  else if (y < 0) y = 0;

  // Actually return the values.
  return (y * GRID_WIDTH) + x;
}

std::tuple<int, int> get_position_at(int index) {
  return {
    index / GRID_WIDTH,
    index % GRID_WIDTH
  };
}

void swap_cells(int index1, int index2) {
  int temp_cell = grid[index1];
  grid[index1] = grid[index2];
  grid[index2] = temp_cell;
}

void do_sand_update (int x, int y) {
  if (y + 1 >= GRID_HEIGHT) return; // Don't bother if out of bounds.

  if (!can_block_sand(grid[get_index_at(x, y + 1)])) { // is thing below
    swap_cells(get_index_at(x, y+1), get_index_at(x, y));
  } else if (!can_block_sand(grid[get_index_at(x - 1, y + 1)])) { // is thing below to the left
    swap_cells(get_index_at(x - 1, y + 1), get_index_at(x, y));
  } else if (!can_block_sand(grid[get_index_at(x + 1, y + 1)])) {
    swap_cells(get_index_at(x + 1, y + 1), get_index_at(x, y));
  }
}

void do_water_update (int x, int y) {
  if (y + 1 >= GRID_HEIGHT) return; // Don't bother if out of bounds.

  if (!can_block_water(grid[get_index_at(x, y + 1)])) { // is thing below
    swap_cells(get_index_at(x, y+1), get_index_at(x, y));
  } else if (!can_block_water(grid[get_index_at(x - 1, y + 1)])) { // is thing below to the left
    swap_cells(get_index_at(x - 1, y + 1), get_index_at(x, y));
  } else if (!can_block_water(grid[get_index_at(x + 1, y + 1)])) {
    swap_cells(get_index_at(x + 1, y + 1), get_index_at(x, y));
  } else {
    int direction = GetRandomValue(0, 1) == 1 ? 1 : -1;
    if (!can_block_water(grid[get_index_at(x + direction, y)])) {
      swap_cells(get_index_at(x + direction, y), get_index_at(x, y));
    }
  }
}

int current_cell_type = 1;
int main() {
  InitWindow(CELL_SIZE * GRID_WIDTH, CELL_SIZE * GRID_HEIGHT, "Falling sand thing");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // --- Input ---
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 mouse = GetMousePosition();
      int x = mouse.x / CELL_SIZE;
      int y = mouse.y / CELL_SIZE;

      if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        grid[get_index_at(x, y)] = current_cell_type;
        grid[get_index_at(x+1, y)] = current_cell_type;
        grid[get_index_at(x-1, y)] = current_cell_type;
        grid[get_index_at(x, y+1)] = current_cell_type;
        grid[get_index_at(x, y-1)] = current_cell_type;
      }
    }
    int keyPressed = GetCharPressed();
    if (keyPressed > '0' && keyPressed < '9') {
      printf("%d\n", keyPressed);
      current_cell_type = keyPressed - 48;
    }

    // --- Update ---
    for (int y = GRID_HEIGHT - 1; y > 0; y--) {
      for (int x = 0; x < GRID_WIDTH; x++) {
        int cell = grid[get_index_at(x, y)];
        switch (cell) {
          case id_sand: // SAND
            do_sand_update(x, y);
            break;

          case id_water: // WATER
            do_water_update(x, y);
            break;

          case id_empty: // AIR
          default: break;
        }
      }
    }

    // --- Drawing ---
    BeginDrawing();
    ClearBackground(WHITE);

    for (int y = 0; y < GRID_HEIGHT; y++) {
      for (int x = 0; x < GRID_WIDTH; x++) {
        Color color = color_map.at(grid[get_index_at(x, y)]);
        DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
      }
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
