#include "Advents.hpp"
#include "core/global.hpp"
#include "imgui/imgui.h"
#include "tools/Logger.hpp"
#include "tools/Math.hpp"
#include "tools/Reader.hpp"
#include <fstream>

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
    ImGui::Separator();
    ImGui::Text("Drag and drop file here!");
    if (!g_dropped_filenames.empty()) {
      for (auto &file : g_dropped_filenames) {
        ImGui::TextWrapped("File dropped: %s", file.c_str());
      }
    }
    if (ImGui::Button("Run Challenge")) {
      std::vector<std::string> input = {"L68", "L30", "R48", "L5",  "R60",
                                        "L55", "L1",  "L99", "R14", "L82"};
      if (!g_dropped_filenames.empty()) {
        input.clear();
        std::ifstream file(g_dropped_filenames[0]);
        std::string str;
        while (std::getline(file, str)) {
          input.push_back(str);
        }
      }

      advent_day_1_pt1(input);
      advent_day_1_pt2(input);
    }
    ImGui::Separator();
    ImGui::TextWrapped("Result:");
    ImGui::SameLine();
    ImGui::TextWrapped("%s", m_result_1.c_str());
    ImGui::TextWrapped("%s", m_result_2.c_str());
    ImGui::End();
    break;
  case DAY_2:
    ImGui::Begin("Day 2: Gift Shop");
    if (ImGui::CollapsingHeader("Read Description")) {
    }
    ImGui::Separator();
    ImGui::Text("Drag and drop file here!");
    if (!g_dropped_filenames.empty()) {
      for (auto &file : g_dropped_filenames) {
        ImGui::TextWrapped("File dropped: %s", file.c_str());
      }
    }
    if (ImGui::Button("Run Challenge")) {
      std::string input = {
          "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-"
          "1698528,446443-446449,38593856-38593862,565653-565659,824824821-"
          "824824827,2121212118-2121212124"};
      if (!g_dropped_filenames.empty()) {
        input.clear();
        std::ifstream file(g_dropped_filenames[0]);
        std::string str;
        while (std::getline(file, str)) {
          input += str;
        }
      }

      advent_day_2_pt1(input);
      advent_day_2_pt2(input);
    }
    ImGui::Separator();
    ImGui::TextWrapped("Result:");
    ImGui::SameLine();
    ImGui::TextWrapped("%s", m_result_1.c_str());
    ImGui::TextWrapped("%s", m_result_2.c_str());
    ImGui::End();
    break;
  default:
    break;
  }
}

void Advents::advent_day_1_pt1(std::vector<std::string> input) {
  int dial = 50;
  int rotated_to_0 = 0;

  for (auto line : input) {
    char direction = line[0];
    int amount = std::stoi(line.substr(1));

    if (direction == 'R') {
      dial = (dial + amount) % 100;
    } else {
      dial = ((dial - amount) % (100) + (100)) % (100);
    }

    if (dial == 0) {
      rotated_to_0++;
    }
  }

  m_result_1 = "Rotated to 0: " + std::to_string(rotated_to_0) + " times.";
}

void Advents::advent_day_1_pt2(std::vector<std::string> input) {

  int dial = 50;
  int dial_buffer = dial;
  int rotated_to_0 = 0;

  for (auto line : input) {
    char direction = line[0];
    int amount = std::stoi(line.substr(1));
    dial_buffer = dial;

    if (direction == 'R') {
      dial = (dial + amount) % 100;
      {
        auto total = dial_buffer + amount;
        if (total != 100) {

          auto total_quo = total / 100;
          Logger::log("Total: " + std::to_string(total));
          Logger::log("Total quo: " + std::to_string(total_quo));
          for (int i = 0; i < total_quo; i++) {
            rotated_to_0++;
          }
        }
      }
    } else {
      dial = ((dial - amount) % (100) + (100)) % (100);
      if (dial_buffer != 0) {
        Logger::log("Dial before subtraction: " + std::to_string(dial));
        Logger::log("Amount to subtract: " + std::to_string(amount));
        int total = dial_buffer - amount;
        if (total < 0) {
          rotated_to_0++;
          int total_quo = Math::abs(total) / 100;
          Logger::log("Total: " + std::to_string(total));
          Logger::log("Total quo: " + std::to_string(total_quo));
          for (int i = 0; i < total_quo; i++) {
            rotated_to_0++;
          }
        }
      }
    }

    if (dial == 0) {
      rotated_to_0++;
    }
  }

  m_result_2 = "Rotated to 0: " + std::to_string(rotated_to_0) + " times.";
}

void Advents::advent_day_2_pt1(std::string input) {
  struct Gift {
    std::string id;
    bool valid = true;
  };

  std::vector<Gift> gifts;
  Gift current_gift;
  std::string current_id = "";
  int sum_gifts = 0;

  for (char c : input) {
    if (c == '-') {
      Logger::log("Found gift - : " + current_id);
      current_gift.id = current_id;
      gifts.push_back(current_gift);
      current_id = "";
      continue;
    }
    if (c == ',') {
      Logger::log("Ending gift ID: " + current_id);
      current_gift.id = current_id;
      gifts.push_back(current_gift);
      current_id = "";
      continue;
    }

    if (current_id.length() > 0) {
      if (c == current_id.back()) {
        current_gift.valid = false;
      }
    }

    current_id += c;
  }

  for (auto gift : gifts) {
    if (gift.id[0] == '0') {
      Logger::log("Gift ID " + gift.id + " is invalid, starts with 0.");
      gift.valid = false;
    }
  }
  for (auto gift : gifts) {
    if (!gift.valid) {
      Logger::log("Gift ID " + gift.id + " is invalid.");
      sum_gifts += std::stoi(gift.id);
    }
  }

  m_result_1 = "Sum of invalid gift IDs: " + std::to_string(sum_gifts);
}

void Advents::advent_day_2_pt2(std::string input) {}
