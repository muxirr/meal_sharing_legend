#ifndef _CURSOR_MGR_H_
#define _CURSOR_MGR_H_

#include "meal.h"

#include <SDL.h>

#include <string>
#include <unordered_map>

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

  Meal meal_picked = Meal::None;   // 当前抓取的物品,
  SDL_Point pos_cursor = {0, 0};   // 鼠标指针的位置,
  bool is_mouse_lbtn_down = false; // 鼠标左键是否按下,
  std::unordered_map<Meal, std::string> meal_picked_map = {
      {Meal::Cola, "cola"},
      {Meal::Sprite, "sprite"},
      {Meal::BraisedChicken_Hot, "bc_hot_picked"},
      {Meal::BraisedChicken_Cold, "bc_cold_picked"},
      {Meal::MeatBall_Hot, "mb_hot_picked"},
      {Meal::MeatBall_Cold, "mb_cold_picked"},
      {Meal::RedCookedPork_Hot, "rcp_hot_picked"},
      {Meal::RedCookedPork_Cold, "rcp_cold_picked"},
      {Meal::BraisedChicken_Box, "bc_box"},
      {Meal::MeatBall_Box, "mb_box"},
      {Meal::RedCookedPork_Box, "rcp_box"},
      {Meal::TakeoutBox, "tb_picked"}};
};

#endif // _CURSOR_MGR_H_