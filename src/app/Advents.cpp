#include "Advents.hpp"
#include "imgui/imgui.h"

Advents::Advents() {}

void Advents::draw() {
  switch (current_day) {
  case DAY_NONE:
    ImGui::Begin("Advents");
    ImGui::Text("Please select a day to see the solution.");
    ImGui::End();
    break;
  case DAY_1:
    ImGui::Begin("Day 1: Secret Entrance");
    if (ImGui::CollapsingHeader("Read Description")) {
    }
    ImGui::End();
    break;
  case DAY_2:
    break;
  default:
    break;
  }
}
