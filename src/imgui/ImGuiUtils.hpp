#pragma once

#include "../tools/Common.hpp"
#include "imgui_impl_opengl3.h"
#include <string>

#define IMRED ImVec4(1.0f, 0.0f, 0.0f, 1.0f)
#define IMGREEN ImVec4(0.0f, 1.0f, 0.0f, 1.0f)
#define IMBLUE ImVec4(0.0f, 0.0f, 1.0f, 1.0f)
#define IMYELLOW ImVec4(1.0f, 1.0f, 0.0f, 1.0f)
#define IMWHITE ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
#define IMBLACK ImVec4(0.0f, 0.0f, 0.0f, 1.0f)

class ImGuiUtils {
public:
  static void header_input_text(const std::string &header, std::string *text);
  static void header_input_int(const std::string &header, int *value);
  static void header_input_float(const std::string &header, float *value);
  static void header_input_bool(const std::string &header, bool *value);
  static void header_input_vec2(const std::string &header, vec2 *value);
  // color stuff
};
