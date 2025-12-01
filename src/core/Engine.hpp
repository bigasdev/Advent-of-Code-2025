/**
  @description not so much to say about this one, is the engine of the game,
here we will instantiate and run everything
**/

#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../tools/Common.hpp"

class SDL_Renderer;
class SDL_Window;
class GPU_Target;
class Profiler;
class App;
class Res;
class InputManager;
class SoundManager;

class Engine {
private:
  enum class LoadState {
    PROFILER,
    RENDERER,
    SOUND,
    INPUT,
    RESOURCES,
    START_APP,
    START_IMGUI
  };

  bool m_running = false;
  bool m_loaded = false;
  LoadState m_load_state = LoadState::PROFILER;
  float m_load_progress = 0.0f;

  SDL_Renderer *m_sdl_renderer;
  SDL_Window *m_sdl_window;
  GPU_Target *m_gpu;
  App *m_app;
  Profiler *m_profiler;
  Res *m_res;
  InputManager *m_input_manager;
  SoundManager *m_sound_manager;

  vec2 m_window_size;

  void load_step();

public:
  Engine();
  ~Engine();

  void init();
  void post_init();
  void fixed_update();
  void update();
  void post_update();
  void input();
  void draw();
  void quit();
  bool is_running() { return m_running; }

  // getters
  vec2 *get_window_size() { return &m_window_size; }
};

#endif
