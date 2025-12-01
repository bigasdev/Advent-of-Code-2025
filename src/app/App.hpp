#pragma once

/*
   Here is where all the game logic will be, the goal is to never touch the
   Engine code, just use this one to manage the game.
 */

#include <memory>
#include <string>
#include <windows.h>
#ifndef APP_HPP
#define APP_HPP

class Fini;

class App {
public:
  App();
  ~App();

  void init();
  void fixed_update(double tmod);
  void update(double dt);
  void post_update(double dt);
  void draw_ui();
  void clean();

private:
  std::unique_ptr<Fini> fini;
};

#endif
