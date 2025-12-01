#include "Engine.hpp"
#include "../app/App.hpp"
#include "../imgui/imgui.h"
#include "../renderer/AppGui.hpp"
#include "../res/Res.hpp"
#include "../tools/Logger.hpp"
#include "../tools/Math.hpp"
#include "../tools/Profiler.hpp"
#include "InputManager.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_hints.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_scancode.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_video.h"
#include "SoundManager.hpp"
#include "Timer.hpp"
#include "global.hpp"
#include <cassert>
#include <iostream>

// init
#ifndef WIN_WIDTH
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#endif

Engine::Engine() { Logger::setup_crash_handlers(); }

Engine::~Engine() {}

void Engine::init() {
  int init = -99;
  Logger::log("Initializing SDL3...");
#ifdef __EMSCRIPTEN__
  init = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
#else
  init = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
#endif
  Logger::log("SDL2 init code: " + std::to_string(init));

  if (init == 0) {
    Logger::log("SDL2 initialized");
    Logger::log_group("SDL2 version", SDL_GetRevision());
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  // get computer resolution
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);

  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI |
                        SDL_WINDOW_RESIZABLE);
  m_sdl_window = SDL_CreateWindow("Game", DM.w - (WIN_WIDTH * 1.1f),
                                  DM.h - (WIN_HEIGHT * 1.1f), WIN_WIDTH,
                                  WIN_HEIGHT, window_flags);
  m_window_size = {WIN_WIDTH, WIN_HEIGHT};

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  SDL_GLContext gl_context = SDL_GL_CreateContext(m_sdl_window);

  if (!SDL_GL_MakeCurrent(m_sdl_window, gl_context)) {
    Logger::log("SDL_GL_MakeCurrent failed");
  }
  SDL_GL_SetSwapInterval(1); // Enable vsync
  SDL_SetWindowPosition(m_sdl_window, SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED);
  SDL_ShowWindow(m_sdl_window);
  // GPU_SetInitWindow(SDL_GetWindowID(m_sdl_window));

  /*m_sdl_renderer =
      SDL_CreateRenderer(m_sdl_window, -1, SDL_RENDERER_ACCELERATED);
  m_gpu = GPU_InitRenderer(GPU_RENDERER_OPENGL_3, WIN_WIDTH, WIN_HEIGHT,
                           SDL_RENDERER_ACCELERATED);

  if (m_gpu != nullptr) {
    Logger::log("SDL3 GPU created");
  }
  if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
    Logger::log("SDL3 image initialized");
  }

  SDL_GL_SetSwapInterval(1);*/

  /*if (Mix_OpenAudio(44100, , 2, 2048) >= 0) {
    Logger::log("SDL3 mixer initialized");
  } else {
    Logger::log("SDL3 mixer failed to initialize " +
                std::string(Mix_GetError()));
  }*/

  if (m_sdl_window != nullptr) {
    Logger::log("SDL2 window created");
  }

  TTF_Init();

  m_running = true;
}

void Engine::post_init() {}

void Engine::load_step() {
  switch (m_load_state) {
  case LoadState::PROFILER:
    m_profiler = new Profiler();
    Logger::log("Profiler initialized");
    m_load_state = LoadState::RENDERER;
    m_load_progress += 5.0f;
    break;
  case LoadState::RENDERER:
    m_load_state = LoadState::SOUND;
    Logger::log("Renderer initialized");
    m_load_progress += 10.0f;
    break;
  case LoadState::SOUND:
    m_sound_manager = new SoundManager();
    g_sound_manager = m_sound_manager;
    m_load_state = LoadState::INPUT;
    Logger::log("Sound manager initialized");
    m_load_progress += 5.0f;
    ;
    break;
  case LoadState::INPUT:
    m_input_manager = new InputManager();
    g_input_manager = m_input_manager;
    m_load_state = LoadState::RESOURCES;
    Logger::log("Input manager initialized");
    m_load_progress += 5.0f;
    break;
  case LoadState::RESOURCES:
    m_res = new Res();
    m_res->init();
    g_engine = this;
    g_res = m_res;
    m_load_state = LoadState::START_APP;
    Logger::log("Resources initialized");
    m_load_progress += 55.0f;
    break;
  case LoadState::START_APP:
    // starting game
    m_app = new App();
    m_app->init();
    Logger::log("Game initialized");
    m_load_state = LoadState::START_IMGUI;
    m_load_progress += 20.0f;
    break;
  case LoadState::START_IMGUI:
    SDL_GLContext gl_context = SDL_GL_GetCurrentContext();
    GUI::setup(m_sdl_window, gl_context);
    Logger::log("Engine post init");
    m_loaded = true;
    break;
  }
}

void Engine::input() {
  if (!m_loaded)
    return;

  SDL_Event event;

  while (SDL_PollEvent(&event) != 0) {
    GUI::event(event);
    g_input_manager->update(event);
    switch (event.type) {
    case SDL_WINDOWEVENT:
      if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
        // updating window size
        {
          int h = 0, w = 0;
          SDL_GetWindowSize(m_sdl_window, &h, &w);
          m_window_size.x = h;
          m_window_size.y = w;
        }
      }
      break;
    case SDL_QUIT:
      m_running = false;
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_ESCAPE:
#if _DEBUG
        m_running = false;
#endif
        break;
      }
    }
  }
}

void Engine::fixed_update() {
  if (!m_loaded) {
    return;
  }

  m_app->fixed_update(Timer::get_tmod());
}

void Engine::update() {
  if (!m_loaded) {
    load_step();
    return;
  }

  g_input_manager->tick_update();
  m_app->update(Timer::get_dt());
}

void Engine::post_update() {
  if (!m_loaded) {
    return;
  }

  m_app->post_update(Timer::get_dt());

#if _DEBUG
  m_profiler->update();
  m_res->update();
#endif
}

void Engine::draw() {
  if (!m_loaded) {
    return;
  }

  /*GPU_Clear(m_gpu);
  if (!m_loaded) {
    GPU_SetCamera(m_gpu, nullptr);
    // loading screen will be here
    std::cout << "Loading... " << m_load_progress << "%\n";
    Rect rect;
    Col col = {255, 0, 0, 255};
    rect.x = m_window_size.x / 4;
    rect.y = m_window_size.y / 2 - 10;
    rect.w = (m_window_size.x / 2) * (m_load_progress / 100.0f);
    rect.h = 20;

    GPU_RectangleFilled(m_gpu, rect.x, rect.y, rect.x + rect.w, rect.y +
rect.h, {col.r, col.g, col.b, col.a});

    GPU_Flip(m_gpu);
    return;
  }

  GPU_SetCamera(m_gpu, nullptr);
#if _DEBUG
  GPU_SetCamera(m_gpu, nullptr);
  m_profiler->draw();
#endif*/
  // GPU_FlushBlitBuffer();

  GUI::draw([&]() { m_app->draw_ui(); });

  // GPU_Flip(m_gpu);
}

void Engine::quit() {
  m_app->clean();
  // SDL_DestroyWindow(SDL_GetWindowFromID(GPU_GetInitWindow()));
  SDL_DestroyWindow(m_sdl_window);
  SDL_Quit();
  Logger::log("SDL2 quit");
  Logger::write_to_file("log.txt");
}
