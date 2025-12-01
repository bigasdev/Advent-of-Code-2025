#pragma once
#include <SDL2/SDL.h>
#include <functional>
#include <stdio.h>

#ifdef _IMGUI
#endif
namespace GUI {
void setup(SDL_Window *window, SDL_GLContext &renderer);
void event(SDL_Event event);
void draw(std::function<void()> function);
void clean();

// util functions
void set_focus();

extern SDL_Window *gui_window;
extern SDL_GLContext gui_renderer;
} // namespace GUI
