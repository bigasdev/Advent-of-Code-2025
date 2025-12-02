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
  void advent_day_1_pt1(std::vector<std::string> input);
  void advent_day_1_pt2(std::vector<std::string> input);

  void advent_day_2_pt1(std::string input);
  void advent_day_2_pt2(std::string input);

private:
  AdventsType current_day = DAY_NONE;

  std::string m_result_1 = "";
  std::string m_result_2 = "";
};
