#include "global.hpp"

Engine *g_engine;
Res *g_res;
Cooldown *g_cooldown;
SoundManager *g_sound_manager;
InputManager *g_input_manager;
TickManager *g_tick_manager;

bool g_left_click;
bool g_controller_connected;
bool g_paused;
bool g_is_dragging_files;

float g_light_falloff;
