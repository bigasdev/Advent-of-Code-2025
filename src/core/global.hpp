#pragma once
#ifndef GLOBAL_HPP
#define GLOBAL_HPP

class Engine;
class Res;
class SoundManager;
class Cooldown;
class InputManager;
class TickManager;

extern Engine *g_engine;
extern Res *g_res;
extern Cooldown *g_cooldown;
extern SoundManager *g_sound_manager;
extern InputManager *g_input_manager;
extern TickManager *g_tick_manager;

extern bool g_left_click;
extern bool g_controller_connected;
extern bool g_paused;

#endif
