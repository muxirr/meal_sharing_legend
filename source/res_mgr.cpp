#include "res_mgr.h"

#include <SDL_image.h>
#include <filesystem>

ResMgr *ResMgr::manager = nullptr;

ResMgr *ResMgr::instance() {
  if (manager == nullptr) {
    manager = new ResMgr();
  }
  return manager;
}

Mix_Chunk *ResMgr::find_audio(const std::string &name) {
  return audio_pool[name];
}

SDL_Texture *ResMgr::find_texture(const std::string &name) {
  return texture_pool[name];
}

ResMgr::ResMgr() = default;

ResMgr::~ResMgr() = default;

void ResMgr::load(SDL_Renderer *renderer) {
  using namespace std::filesystem;
  auto dir = path("../../assets");
  if(!exists(dir)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "assets文件夹不存在", NULL);
  }
  for (const auto &entry : recursive_directory_iterator(dir)) {
    if (entry.is_regular_file()) {
      auto path = entry.path();
      auto name = path.stem().string();
      auto ext = path.extension().string();
      if (ext == ".mp3") {
        audio_pool[name] = Mix_LoadWAV(
            reinterpret_cast<const char *>(path.u8string().c_str()));
      } else if (ext == ".png") {
        texture_pool[name] = IMG_LoadTexture(
            renderer, reinterpret_cast<const char *>(path.u8string().c_str()));
      }
    }
  }
}