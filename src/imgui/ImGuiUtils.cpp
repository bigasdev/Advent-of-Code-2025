#include "ImGuiUtils.hpp"
#include "imgui_stdlib.h"

void ImGuiUtils::header_input_text(const std::string &header,
                                   std::string *text) {
  ImGui::Text(header.c_str());
  ImGui::SameLine();
  ImGui::InputText(("##" + header).c_str(), text);
  ImGui::Separator();
}

void ImGuiUtils::header_input_int(const std::string &header, int *value) {
  ImGui::Text(header.c_str());
  ImGui::SameLine();
  ImGui::InputInt(("##" + header).c_str(), value);
  ImGui::Separator();
}

void ImGuiUtils::header_input_float(const std::string &header, float *value) {
  ImGui::Text(header.c_str());
  ImGui::SameLine();
  ImGui::InputFloat(("##" + header).c_str(), value);
  ImGui::Separator();
}

void ImGuiUtils::header_input_bool(const std::string &header, bool *value) {
  ImGui::Text(header.c_str());
  ImGui::SameLine();
  ImGui::Checkbox(("##" + header).c_str(), value);
  ImGui::Separator();
}

void ImGuiUtils::header_input_vec2(const std::string &header, vec2 *value) {
  ImGui::Text(header.c_str());
  ImGui::SameLine();
  ImGui::SetNextItemWidth(60);
  ImGui::InputFloat(("##" + header + "_x").c_str(), &value->x);
  ImGui::SameLine();
  ImGui::SetNextItemWidth(60);
  ImGui::InputFloat(("##" + header + "_y").c_str(), &value->y);
  ImGui::Separator();
}
