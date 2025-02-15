#ifndef _BUNDLE_H_
#define _BUNDLE_H_

#include "meal.h"
#include "region.h"
#include <string>



class Bundle : public Region {
public:
  Bundle(int x, int y, Meal meal) : meal_bundle(meal) {
    switch (meal) {
    case Meal::BraisedChicken_Box:
      bundle_name = "bc_box_bundle";
      break;
    case Meal::MeatBall_Box:
      bundle_name = "mb_box_bundle";
      break;
    case Meal::RedCookedPork_Box:
      bundle_name = "rcp_box_bundle";
      break;
    case Meal::Cola:
      bundle_name = "cola_bundle";
      break;
    case Meal::Sprite:
      bundle_name = "sprite_bundle";
      break;
    case Meal::TakeoutBox:
      bundle_name = "tb_bundle";
      break;
    default:
      break;
    }
    if (meal_bundle == Meal::BraisedChicken_Box ||
        meal_bundle == Meal::MeatBall_Box ||
        meal_bundle == Meal::RedCookedPork_Box) {
      rect = {x, y, 160, 88};
    } else if (meal_bundle == Meal::Cola || meal_bundle == Meal::Sprite) {
      rect = {x, y, 120, 124};
    } else if (meal_bundle == Meal::TakeoutBox) {
      rect = {x, y, 112, 96};
    }
  }

  ~Bundle() = default;

  void on_render(SDL_Renderer *renderer) override;
  void on_cursor_down() override;
  void on_cursor_up() override;

private:
  Meal meal_bundle = Meal::None;
  std::string bundle_name;
};

#endif // _BUNDLE_H_