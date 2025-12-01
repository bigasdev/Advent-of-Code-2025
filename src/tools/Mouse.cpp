#include "Mouse.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mouse.h"
#include <cmath>
#include <cstdlib>

#include "core/Engine.hpp"
#include "core/global.hpp"
#include "tools/Logger.hpp"
#include <string>

namespace Mouse {
bool is_clicked;
}

bool Mouse::is_at_area(Rect pArea) {
  int x = 0, y = 0;
  SDL_GetMouseState(&x, &y);

  // explanation of the magic numbers:
  // 4 are used to smoothen the edge-case detection
  // 8x8 is the width of the default cursor
  Rect mouseArea = Rect(x - 4, y - 4, 8, 8);
  return mouseArea.intersects(pArea);
}

Rect Mouse::get_mouse_area(int width, int height) {
  int x = 0, y = 0;
  SDL_GetMouseState(&x, &y);

  int scaled_x = x * 64 / width;
  int scaled_y = y * 64 / height;

  return Rect(scaled_x - 4, scaled_y - 4, 8, 8);
}

vec2 Mouse::get_mouse_pos() {
  int x = 0, y = 0;
  SDL_GetMouseState(&x, &y);
  return vec2(x, y);
}
