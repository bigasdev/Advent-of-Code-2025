#pragma once
#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Common.hpp"
namespace Mouse {

bool is_at_area(Rect pArea);
Rect get_mouse_area(int width, int height);
vec2 get_mouse_pos();

extern bool is_clicked;
}; // namespace Mouse

#endif
