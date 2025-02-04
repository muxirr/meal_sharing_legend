#include "cursor_mgr.h"
#include "res_mgr.h"

CursorMgr *CursorMgr::manager = nullptr;

CursorMgr *CursorMgr::instance() {
  if (manager == nullptr) {
    manager = new CursorMgr();
  }
  return manager;
}

CursorMgr::CursorMgr() {
  meal_callbacks.push_back(nullptr);
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("cola");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("sprite");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("bc_hot_picked");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("bc_cold_picked");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("mb_hot_picked");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("mb_cold_picked");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("rcp_hot_picked");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("rcp_cold_picked");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("bc_box");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("mb_box");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("rcp_box");
  });
  meal_callbacks.push_back([&](SDL_Renderer *renderer) {
    return ResMgr::instance()->find_texture("tb_picked");
  });
}

CursorMgr::~CursorMgr() = default;

void CursorMgr::on_input(const SDL_Event &event) {
  switch (event.type) {
  case SDL_MOUSEMOTION:
    pos_cursor.x = event.motion.x;
    pos_cursor.y = event.motion.y;
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (event.button.button == SDL_BUTTON_LEFT) {
      is_mouse_lbtn_down = true;
      switch (rand() % 3) {
      case 0:
        Mix_PlayChannel(-1, ResMgr::instance()->find_audio("click_1"), 0);
        break;
      case 1:
        Mix_PlayChannel(-1, ResMgr::instance()->find_audio("click_2"), 0);
        break;
      case 2:
        Mix_PlayChannel(-1, ResMgr::instance()->find_audio("click_3"), 0);
        break;
      }
    }
    break;
  case SDL_MOUSEBUTTONUP:
    if (event.button.button == SDL_BUTTON_LEFT) {
      is_mouse_lbtn_down = false;
    }
    break;
  }
}

void CursorMgr::on_render(SDL_Renderer *renderer) {
  // 绘制拿起的物品,
  if (meal_picked != Meal::None) {
    SDL_Texture *texture =
        meal_callbacks[static_cast<int>(meal_picked)](renderer);
    SDL_Rect rect_picked = {pos_cursor.x, pos_cursor.y, 0, 0};
    SDL_QueryTexture(texture, nullptr, nullptr, &rect_picked.w, &rect_picked.h);
    SDL_RenderCopy(renderer, texture, nullptr, &rect_picked);
  }

  // 绘制鼠标指针,
  SDL_Rect rect_cursor = {pos_cursor.x, pos_cursor.y, 64, 64};
  SDL_Texture *texture_cursor = ResMgr::instance()->find_texture(
      is_mouse_lbtn_down ? "cursor_down" : "cursor_idle");
  SDL_RenderCopy(renderer, texture_cursor, nullptr, &rect_cursor);
}

void CursorMgr::set_picked(Meal meal) { meal_picked = meal; }

Meal CursorMgr::get_picked() { return meal_picked; }