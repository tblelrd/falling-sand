// Code yonked from https://gist.github.com/ciembor/1494530

#define MAX(a,b) ((a)<(b)?(a):(b))
#define MIN(a,b) ((a)>(b)?(a):(b))

#include "raylib.h"
#include "colors.h"

ColorHSL rgb_to_hsl (Color color) {
  ColorHSL result;

  float r = color.r / 255.0;
  float g = color.g / 255.0;
  float b = color.b / 255.0;

  float a = color.a / 255.0;

  float max = MAX(MAX(r, g), b);
  float min = MIN(MIN(r, g), b);

  result.h = result.s = result.l = (max + min) / 2;
  result.a = a;

  if (max == min) {
    result.h = result.s = 0; // Achromatic
  }
  else {
    // Honestly no clue
    float diff = max - min;
    result.s = (result.l > 0.5) ?
      diff / (2 - max - min) : 
      diff / (max + min);

    if (max == r) {
      result.h = (g - b) / diff + (g < b ? 6 : 0);
    }
    else if (max == g) {
      result.h = (b - r) / diff + 2;
    }
    else if (max == b) {
      result.h = (r - g) / diff + 4;
    }

    result.h /= 6;
  }

  return result;
}

float hue_to_rgb (float p, float q, float t) {
  if (t < 0) 
    t += 1;
  if (t > 1) 
    t -= 1;
  if (t < 1./6) 
    return p + (q - p) * 6 * t;
  if (t < 1./2) 
    return q;
  if (t < 2./3)   
    return p + (q - p) * (2./3 - t) * 6;
    
  return p;
}

Color hsl_to_rgb (ColorHSL color) {
  Color result;
  result.a = (color.a * 255);

  if (0 == color.s) {
    result.r = result.g = result.b = color.l * 255;
  }
  else {
    float q = color.l < 0.5 ? color.l * (1 + color.s) : color.l + color.s - color.l * color.s;
    float p = 2 * color.l - q;

    result.r = hue_to_rgb(p, q, color.h + 1./3) * 255;
    result.g = hue_to_rgb(p, q, color.h) * 255;
    result.b = hue_to_rgb(p, q, color.h - 1./3) * 255;
  }

  return result;
}
