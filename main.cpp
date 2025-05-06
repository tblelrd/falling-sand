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
#define id_stone (u8) 3

// --- GLOBALS ---
const int CELL_SIZE = 10;
const int GRID_WIDTH = 80;
const int GRID_HEIGHT = 60;

std::unordered_map<u8, Color> color_map = {
    {id_empty, LIGHTGRAY}, // AIR
    {id_sand, YELLOW},    // SAND
    {id_water, SKYBLUE},    // WATER??
    {id_stone, GRAY}    // WATER??
};

// --- STRUCTS ---
struct Particle {
  u8 id;
  int vx;
  int vy;
  Color color;
  bool has_updated;

  Particle(u8 p_id, int p_vx, int p_vy) {
    id=p_id;
    vx=p_vx;
    vy=p_vy;
    color=color_map.at(id);
    has_updated=false;
  }
  Particle(u8 p_id) : Particle(p_id, 0, 0) {}
  Particle() : Particle(id_empty) {}
};

// GRID
Particle* grid[GRID_WIDTH * GRID_HEIGHT] = {};
Particle* updated_grid[GRID_WIDTH * GRID_HEIGHT] = {};

// --- FUNCTIONS ---
void initialize_grid() {
  for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
    grid[i] = new Particle();
  }
}

bool can_block_sand(Particle* particle_p) {
  Particle particle = *particle_p;

  if (particle.id == id_stone) return true; 
  if (particle.id == id_sand) return true;
  return false;
}

bool can_block_water(Particle* particle_p) {
  Particle particle = *particle_p;

  if (particle.id > 0) return true;
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

std::pair<int, int> get_position_at(int index) {
  return {
    index % GRID_WIDTH,
    index / GRID_WIDTH,
  };
}

Particle* get_particle_at(int x, int y) {
  return grid[get_index_at(x, y)];
}

Particle* get_particle_at(int index) {
  return grid[index];
}

void swap_cells(int index_to, int index_from) {
  Particle *temp_cell = grid[index_to];
  grid[index_to] = grid[index_from];
  grid[index_from] = temp_cell;
}

void do_sand_update (int x, int y) {
  if (y + 1 >= GRID_HEIGHT) return; // Don't bother if out of bounds.

  Particle &sand = *get_particle_at(x, y);

  if (!can_block_sand(grid[get_index_at(x, y + 1)])) { // is thing below
    swap_cells(get_index_at(x, y+1), get_index_at(x, y));
  } else if (!can_block_sand(grid[get_index_at(x - 1, y + 1)])) { // is thing below to the left
    swap_cells(get_index_at(x - 1, y + 1), get_index_at(x, y));
  } else if (!can_block_sand(grid[get_index_at(x + 1, y + 1)])) {
    swap_cells(get_index_at(x + 1, y + 1), get_index_at(x, y));
  }

  sand.has_updated = true;
}

void do_water_update (int x, int y) {
  if (y + 1 >= GRID_HEIGHT) return; // Don't bother if out of bounds.

  Particle &water = *get_particle_at(x, y);

  if (!can_block_water(grid[get_index_at(x, y + 1)])) { // is thing below
    swap_cells(get_index_at(x, y+1), get_index_at(x, y));
  } else if (!can_block_water(grid[get_index_at(x + 1, y + 1)])) {
    swap_cells(get_index_at(x + 1, y + 1), get_index_at(x, y));
  } else if (!can_block_water(grid[get_index_at(x - 1, y + 1)])) { // is thing below to the left
    swap_cells(get_index_at(x - 1, y + 1), get_index_at(x, y));
  } else if (water.vx != 0) {
    if (can_block_water(grid[get_index_at(x + water.vx, y)])) {
      Particle p = *get_particle_at(x, y);
      bool p_going_right = p.vx > 0;
      bool w_going_right = water.vx > 0;
      if (!(p_going_right == w_going_right)) water.vx *= -1;
    } 
    if (!can_block_water(grid[get_index_at(x + water.vx, y)])){
      swap_cells(get_index_at(x + water.vx, y), get_index_at(x, y));
    } else {
      water.vx = 0;
    }
  } else {
    if (
      can_block_water(grid[get_index_at(x + 1, y)])
      && can_block_water(grid[get_index_at(x - 1, y)])
    ) {}
    else {
      int direction = GetRandomValue(0, 1) == 1 ? 1 : -1;
      water.vx = direction;
      swap_cells(get_index_at(x + direction, y), get_index_at(x, y));
    }
  }

  water.has_updated = true;
}

int current_cell_type = 1;
int main() {
  InitWindow(CELL_SIZE * GRID_WIDTH, CELL_SIZE * GRID_HEIGHT, "Falling sand thing");
  SetTargetFPS(60);
  initialize_grid();

  while (!WindowShouldClose()) {
    // --- Input ---
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 mouse = GetMousePosition();
      int x = mouse.x / CELL_SIZE;
      int y = mouse.y / CELL_SIZE;

      if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        grid[get_index_at(x, y)] = new Particle(current_cell_type);
        grid[get_index_at(x+1, y)] = new Particle(current_cell_type);
        grid[get_index_at(x-1, y)] = new Particle(current_cell_type);
        grid[get_index_at(x, y+1)] = new Particle(current_cell_type);
        grid[get_index_at(x, y-1)] = new Particle(current_cell_type);
      }
    }
    int keyPressed = GetCharPressed();
    if (keyPressed > '0' && keyPressed < '9') {
      printf("%d\n", keyPressed - 48);
      current_cell_type = keyPressed - 48;
    }

    // --- Update ---
    for (int y = GRID_HEIGHT - 1; y >= 0; y--) {
    // for (int y = 0; y < GRID_HEIGHT; y++) {
      // for (int x = 0; x < GRID_WIDTH; x++) {
      for (int x = GRID_WIDTH - 1; x >= 0; x--) {
        Particle cell = *grid[get_index_at(x, y)];
        if (cell.has_updated) continue;

        switch (cell.id) {
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

    for (int y = 0; y < GRID_HEIGHT; y++) {
      for (int x = 0; x < GRID_WIDTH; x++) {
        get_particle_at(x, y)->has_updated = false;
      }
    }

    // --- Drawing ---
    BeginDrawing();
    ClearBackground(WHITE);

    for (int y = 0; y < GRID_HEIGHT; y++) {
      for (int x = 0; x < GRID_WIDTH; x++) {
        // Color color = grid[get_index_at(x, y)].color;
        Color color = color_map.at(grid[get_index_at(x, y)]->id);
        DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
      }
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
