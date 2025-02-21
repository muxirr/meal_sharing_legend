#ifndef _TAKEOUT_BOX_H_
#define _TAKEOUT_BOX_H_

#include "meal.h"
#include "region.h"

class TakeoutBox : public Region {
public:
  TakeoutBox(int x, int y) { rect = {x, y, 92, 32}; }

  ~TakeoutBox() = default;

  void on_render(SDL_Renderer *renderer) override;
  void on_cursor_down() override;
  void on_cursor_up() override;

private:
  Meal meal = Meal::TakeoutBox;

private:
  bool can_place(Meal target);
};

#endif // TAKEOUT_BOX_H_