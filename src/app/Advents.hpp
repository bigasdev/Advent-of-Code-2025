#pragma once

enum AdventsType {
  DAY_1,
  DAY_2,
};

class Advents {
public:
  Advents();
  void draw();

  void set_current_day(AdventsType day) { current_day = day; }

private:
  AdventsType current_day = DAY_1;
};
