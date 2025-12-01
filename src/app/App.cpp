#include "App.hpp"
#include "SDL2/SDL_keycode.h"
#include "core/InputManager.hpp"
#include "core/engine_commons.hpp"

#include "core/global.hpp"
#include "imgui/ImGuiUtils.hpp"
#include "res/autogen_res.hpp"

// SDL
#include "SDL2/SDL.h"

// Imgui
#include "Advents.hpp"
#include "Fini.hpp"
#include "imgui/imgui.h"
#include <handleapi.h>
#include <minwinbase.h>
#include <synchapi.h>
#include <winerror.h>

// local vars
std::unique_ptr<Advents> advents = std::make_unique<Advents>();

App::App() {}

App::~App() {}

void App::init() { fini = std::make_unique<Fini>("app.ini"); }

void App::fixed_update(double tmod) {}

void App::update(double dt) {
#if _DEBUG
#endif
}

void App::post_update(double dt) {
  if (g_input_manager->get_key_press(SDLK_s, SDLK_LCTRL)) {
    fini->save();
  }
}

void App::draw_ui() {
  ImGui::Begin("Advent of Code 2025");
  ImGui::Text("Select the day to see the solution:");
  if (ImGui::Button("Day 1")) {
    advents->set_current_day(DAY_1);
    //
  }
  ImGui::End();

  advents->draw();
}

void App::clean() {}
