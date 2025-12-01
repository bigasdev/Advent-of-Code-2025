#include "Res.hpp"
#include "../core/Engine.hpp"
#include "../core/SoundManager.hpp"
#include "../core/global.hpp"
#include "../tools/Reader.hpp"
#include "SDL2/SDL_filesystem.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include <string>

Res::Res() {}

Res::~Res() {}

void Res::init() {
  load_fonts();
  load_sounds();
  load_assets();
}

void Res::load_fonts() {
  auto files = Reader::read_file("res/font");

  for (auto file : files) {
    std::string path = file;
    std::string file_name = path.substr(path.find_last_of("/\\") + 1);

    if (file_name.find("-") == std::string::npos) {
      Logger::error("Font file name must contain size, e.g. fontname-16.ttf: " +
                    file_name);
      continue;
    }

    std::string font_size = file_name.substr(file_name.find_last_of("-") + 1);
    font_size = font_size.substr(0, font_size.find_last_of("."));
    Logger::log_group("Font size: ", font_size);
    file_name = file_name.substr(0, file_name.find_last_of("-"));
    Logger::log("Loading font: " + file_name);
    TTF_Font *font = TTF_OpenFont(path.c_str(), std::stoi(font_size));
    if (font == nullptr) {
      Logger::error("Failed to load font: " + path);
    } else {
      Logger::log("Loaded font: " + path);
      m_fonts.insert(std::make_pair(file_name, font));
    }
  }
}

void Res::load_sounds() {
  auto sounds = Reader::get_extension_files("res/sounds", ".wav");

  for (auto sound : sounds) {
    std::string path = sound;
    std::string file_name = path.substr(path.find_last_of("/\\") + 1);
    file_name = file_name.substr(0, file_name.find_last_of("."));
    Logger::log("Loading sound: " + file_name);
    g_sound_manager->load_sound(path.c_str(), file_name);
  }
}

//"assets" are the png files
void Res::load_assets() {
  /*auto files = Reader::get_extension_files("res/assets", ".png");
  m_asset_textures.clear();

  for (auto file : files) {
    std::string path = file;
    std::string file_name = path.substr(path.find_last_of("/\\") + 1);
    file_name = file_name.substr(0, file_name.find_last_of("."));
    Logger::log("Loading asset: " + file_name);

    SDL_Surface *image_data = SDL_LoadBMP(file.c_str());
    if (!image_data) {
      Logger::error("Failed to load asset: " + file);
      continue;
    }

    SDL_GPUTextureCreateInfo texture_info = {
        .type = SDL_GPU_TEXTURETYPE_2D,
        .format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
        .width = (Uint32)image_data->w,
        .height = (Uint32)image_data->h,
        .layer_count_or_depth = 1,
    };

    SDL_GPUTexture *texture =
        SDL_CreateGPUTexture(SDL_GPUDevice * device, texture_info);

    m_asset_textures.insert(
        std::pair<const char *, SDL_GPUTexture *>(file_name.c_str(), texture));
    Logger::log("Asset loaded: " + file_name);
  }*/
}

/*GPU_Image **Res::get_asset(std::string name) {
  try {
    return &m_asset_textures.at(name);
  } catch (const std::out_of_range &e) {
    Logger::error("Asset Texture " + std::string(name) + " not found!");
    return nullptr;
  }
}*/

void Res::update() {
#if _DEBUG
#endif
}
