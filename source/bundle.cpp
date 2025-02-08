#include "bundle.h"
#include "cursor_mgr.h"
#include "res_mgr.h"

void Bundle::on_cursor_up() {
  if (CursorMgr::instance()->get_picked() == bundle_meal) {
    CursorMgr::instance()->set_picked(Meal::None);
  }
}

void Bundle::on_cursor_down() {
  if (CursorMgr::instance()->get_picked() == Meal::None) {
    CursorMgr::instance()->set_picked(bundle_meal);
  }
}

void Bundle::on_render(SDL_Renderer *renderer) {
  SDL_Texture *texture = ResMgr::instance()->find_texture(type);
  SDL_RenderCopy(renderer, texture, nullptr, &rect);
}