#pragma once

#include <string>
#include <vector>
enum AdventsType {
  DAY_NONE,
  DAY_1,
  DAY_2,
};

class Advents {
public:
  Advents();
  void draw();

  void set_current_day(AdventsType day) { current_day = day; }

  // all the challenges
  void advent_day_1(std::vector<std::string> input);

private:
  AdventsType current_day = DAY_NONE;

  std::string m_result = "";
};
