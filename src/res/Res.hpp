#pragma once
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_stdinc.h"
#include <memory>
#include <unordered_map>
#ifndef RES_HPP
#define RES_HPP
#include "../tools/Common.hpp"
#include "SDL2/SDL_ttf.h"

#include "autogen_res.hpp"
#include "tools/Logger.hpp"
#include <iostream>
#include <map>
#include <vector>

class Sprite;
class SpriteFrame;

// TODO: fully rewrite the texture/image loading for SDL3
// it will use just the base renderer, no need to get complex on the basic
// framework

class Res {
public:
  Res();
  ~Res();

  void init();
  void update();

  void load_folder(std::string path);

  // loaders
  void load_fonts();
  void load_sounds();
  void load_assets();

  // getters
  TTF_Font *get_font(std::string name) { return m_fonts[name]; }
  // SDL_GPUTexture **get_asset(std::string name);

private:
  // std::map<std::string, SDL_GPUTexture *> m_asset_textures;
  std::map<std::string, TTF_Font *> m_fonts;
  // std::map<std::string, Sprite> m_sprites;
};
#endif
