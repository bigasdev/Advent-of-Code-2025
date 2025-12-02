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
#include <shellapi.h>
#include <synchapi.h>
#include <winerror.h>
#include <winuser.h>

// local vars
std::unique_ptr<Advents> advents = std::make_unique<Advents>();
HDROP hDrop = nullptr;

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

  if (g_is_dragging_files) // somehow set to true when dragging files on top of
                           // your application
  {
    if (ImGui::BeginDragDropSource(
            ImGuiDragDropFlags_SourceExtern)) // we use an external source (i.e.
                                              // not ImGui-created)
    {
      // replace "FILES" with whatever identifier you want - possibly dependant
      // upon what type of files are being dragged you can specify a payload
      // here with parameter 2 and the sizeof(parameter) for parameter 3. I
      // store the payload within a vector of strings within the application
      // itself so don't need it.
      ImGui::SetDragDropPayload("FILES", nullptr, 0);
      ImGui::BeginTooltip();
      ImGui::Text("FILES");
      ImGui::EndTooltip();
      ImGui::EndDragDropSource();
    }
  }

  if (ImGui::Button("Day 1")) {
    advents->set_current_day(DAY_1);
  }
  if (ImGui::Button("Day 2")) {
    advents->set_current_day(DAY_2);
  }
  ImGui::End();

  advents->draw();
}

void App::clean() {}
