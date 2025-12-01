#include "Advents.hpp"
#include "imgui/imgui.h"
#include "tools/Logger.hpp"

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
    if (ImGui::Button("Run Challenge")) {
      std::vector<std::string> input = {"L68", "L30", "R48", "L5",  "R60",
                                        "L55", "L1",  "L99", "R14", "L82"};
      advent_day_1(input);
    }
    ImGui::Separator();
    ImGui::TextWrapped("Result:");
    ImGui::SameLine();
    ImGui::TextWrapped("%s", m_result.c_str());
    ImGui::End();
    break;
  case DAY_2:
    break;
  default:
    break;
  }
}

void Advents::advent_day_1(std::vector<std::string> input) {
  int dial = 50;
  int rotated_to_0 = 0;

  for (auto line : input) {
    char direction = line[0];
    int amount = std::stoi(line.substr(1));

    if (direction == 'L') {
      dial -= amount;
      if (dial < 0) {
        dial += 100;
      }
    } else if (direction == 'R') {
      dial += amount;
      if (dial > 99) {
        dial -= 100;
      }
    }
    if (dial == 0) {
      rotated_to_0++;
    }

    Logger::log("Direction: " + std::string(1, direction) + " Amount: " +
                std::to_string(amount) + " New Dial: " + std::to_string(dial));
  }

  m_result = "Final Dial Position: " + std::to_string(dial) +
             "\nRotated to 0: " + std::to_string(rotated_to_0) + " times.";
}
