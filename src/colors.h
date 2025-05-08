#ifndef COLORS_H
#define COLORS_H

#include "raylib.h"

struct ColorHSL {
  float h;
  float s;
  float l;
  float a;
};

/**
 * Convert from Raylib's rgb Color struct to my ColorHSL struct.
 */
ColorHSL rgb_to_hsl (Color color); 

/**
 * Converts a HUE to an r, g, or b
 * returns the float in the set of [0, 1].
 */
float hue_to_rgb (float p, float q, float t);

/**
 * Convert a ColorHSL struct to a Color struct
 */
Color hsl_to_rgb (ColorHSL color);

#endif
