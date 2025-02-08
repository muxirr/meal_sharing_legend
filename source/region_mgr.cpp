
#include "region_mgr.h"

RegionMgr *RegionMgr::manager = nullptr;

RegionMgr *RegionMgr::instance() {
  if (manager == nullptr) {
    manager = new RegionMgr();
  }
  return manager;
}

void RegionMgr::add(const std::string &name, Region *region) {
  region_pool[name] = region;
}

Region *RegionMgr::find(const std::string &name) { return region_pool[name]; }

void RegionMgr::on_update(float delta) {
  for (auto &region : region_pool) {
    region.second->on_update(delta);
  }
}

void RegionMgr::on_render(SDL_Renderer *renderer) {
  for (auto &region : region_pool) {
    region.second->on_render(renderer);
  }
}

void RegionMgr::on_input(const SDL_Event &event) {
  switch (event.type) {
  case SDL_MOUSEBUTTONDOWN:
    if (event.button.button == SDL_BUTTON_LEFT) {
      SDL_Point pos_curson = {event.motion.x, event.motion.y};
      for (auto &region : region_pool) {
        if (SDL_PointInRect(&pos_curson, &region.second->get_rect())) {
          region.second->on_cursor_down();
        }
      }
    }
    break;
  case SDL_MOUSEBUTTONUP:
    if (event.button.button == SDL_BUTTON_LEFT) {
      SDL_Point pos_curson = {event.motion.x, event.motion.y};
      for (auto &region : region_pool) {
        if (SDL_PointInRect(&pos_curson, &region.second->get_rect())) {
          region.second->on_cursor_up();
        }
      }
    }
    break;
  }
}