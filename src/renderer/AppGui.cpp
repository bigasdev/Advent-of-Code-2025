#include "AppGui.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#include <SDL2/SDL_opengl.h>

SDL_Window *GUI::gui_window = nullptr;
SDL_GLContext GUI::gui_renderer = nullptr;

void GUI::setup(SDL_Window *window, SDL_GLContext &renderer) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  (void)io;

  // io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

  // styling
  ImGuiStyle &style = ImGui::GetStyle();
  style.WindowRounding = 0;
  style.WindowTitleAlign = ImVec2(0.05f, 0.5f);
  style.WindowBorderSize = 0;
  style.FrameRounding = 0;
  style.ScrollbarRounding = 0;
  style.FramePadding = ImVec2(4, 2);
  style.ChildRounding = 0;
  style.Colors[ImGuiCol_Button] = ImVec4{0.25f, 0.29f, 0.43f, 0};
  // style.Colors[ImGuiCol_ChildBg] = ImVec4{0.15f, 0.15f, 0.15f, 1};
  style.Colors[ImGuiCol_WindowBg] = ImVec4{0.17f, 0.17f, 0.17f, 1.0f};
  // style.Colors[ImGuiCol_Header] = ImVec4{0.25f, 0.29f, 0.43f, 0};
  // style.Colors[ImGuiCol_ButtonActive] = ImVec4{0.34f, 0.43f, 0.25f, 0};
  // style.Colors[ImGuiCol_ButtonHovered] = ImVec4{0.39f, 0.45f, 0.57f, 1.0f};
  // style.Colors[ImGuiCol_Border] = ImVec4{0.39f, 0.45f, 0.57f, .4f};
  // style.Colors[ImGuiCol_TitleBg] = ImVec4{0.25f, 0.29f, 0.43f, 1.0f};
  // style.Colors[ImGuiCol_TitleBgActive] = ImVec4{0.34f, 0.43f, 0.25f, 1.0f};

  // adding custom font
  io.Fonts->AddFontFromFileTTF("res/font/gohufontbig-14.ttf", 14);

  // ImGui::StyleColorsDark();

  GUI::gui_window = window;
  GUI::gui_renderer = renderer;

  ImGui_ImplSDL2_InitForOpenGL(window, renderer);
  ImGui_ImplOpenGL3_Init("#version 130");
}

void GUI::event(SDL_Event event) { ImGui_ImplSDL2_ProcessEvent(&event); }

void GUI::draw(std::function<void()> function) {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
  ImGuiIO &io = ImGui::GetIO();
  // dock
  ImGui::DockSpaceOverViewport();
  (void)io;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // add here our GUI render
  {
    if (function)
      function();
    bool isOpen = true;
    // ImGui::ShowDemoWindow(&isOpen);

    // example of a window
    /*
    ImGui::Begin("Hello World!");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
    ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); ImGui::End();
    */
  }

  // rendering
  ImGui::Render();
  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(GUI::gui_window);
}

void GUI::clean() {
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
}

// we will check some stuff so we can focus the keyboard without breaking
// anything else
void GUI::set_focus() {
  if (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
    ImGui::SetKeyboardFocusHere(0);
}
