#ifndef _BUNDLE_H_
#define _BUNDLE_H_

#include "meal.h"
#include "region.h"
#include <string>

class Bundle : public Region {
public:
  Bundle(int x, int y, Meal meal) : bundle_meal(meal) {
    switch (meal) {
    case Meal::BraisedChicken_Box:
      type = "bc_box_bundle";
      break;
    case Meal::MeatBall_Box:
      type = "mb_box_bundle";
      break;
    case Meal::RedCookedPork_Box:
      type = "rcp_box_bundle";
      break;
    case Meal::Cola:
      type = "cola_bundle";
      break;
    case Meal::Sprite:
      type = "sprite_bundle";
      break;
    case Meal::TakeoutBox:
      type = "tb_bundle";
      break;
    default:
      break;
    }
    if (bundle_meal == Meal::BraisedChicken_Box ||
        bundle_meal == Meal::MeatBall_Box ||
        bundle_meal == Meal::RedCookedPork_Box) {
      rect = {x, y, 160, 88};
    } else if (bundle_meal == Meal::Cola || bundle_meal == Meal::Sprite) {
      rect = {x, y, 120, 124};
    } else if (bundle_meal == Meal::TakeoutBox) {
      rect = {x, y, 112, 96};
    }
  }

  ~Bundle() = default;

  void on_render(SDL_Renderer *renderer) override;
  void on_cursor_down() override;
  void on_cursor_up() override;

private:
  Meal bundle_meal = Meal::None;
  std::string type;
};

#endif // _BUNDLE_H_