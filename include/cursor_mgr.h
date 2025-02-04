#ifndef _CURSOR_MGR_H_
#define _CURSOR_MGR_H_

#include "meal.h"

#include <SDL.h>

#include <functional>
#include <vector>

class CursorMgr {
public:
  static CursorMgr *instance();

  void on_input(const SDL_Event &event);
  void on_render(SDL_Renderer *renderer);

  void set_picked(Meal meal);
  Meal get_picked();

private:
  CursorMgr();
  ~CursorMgr();

private:
  static CursorMgr *manager;

  Meal meal_picked = Meal::None; // 当前抓取的物品,
  std::vector<std::function<SDL_Texture *(SDL_Renderer *)>>
      meal_callbacks;              // 物品抓取的回调函数,
  SDL_Point pos_cursor = {0, 0};   // 鼠标指针的位置,
  bool is_mouse_lbtn_down = false; // 鼠标左键是否按下,
};

#endif // _CURSOR_MGR_H_