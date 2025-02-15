#ifndef _DELIVERY_DRIVER_H_
#define _DELIVERY_DRIVER_H_

#include "meal.h"
#include "region.h"
#include "timer.h"

#include <vector>

class DeliveryDriver : public Region {
public:
  DeliveryDriver(int x, int y);
  ~DeliveryDriver() = default;

  void on_cursor_up() override;
  void on_update(float delta) override;
  void on_render(SDL_Renderer *renderer) override;

private:
  // 餐品状态;
  enum class Status {
    Waiting,   // 等待;
    Completed, // 完成;
  };

private:
  Timer timer_refreash;               // 外卖员刷新定时器;
  float time_waited = 0;              // 已等待时间;
  bool is_waiting = false;            // 是否正在等待;
  bool is_meituan = false;            // 是否是美团外卖;
  std::vector<Meal> meal_list;        // 餐品列表;
  std::vector<Status> status_list;    // 餐品状态列表;
  int num_drink = 0;                  // 饮料数量;
  int num_dish = 0;                   // 菜品数量;
  const float time_wait_limited = 40; // 等待时间限制;

private:
  void refresh();
  bool check_and_place(Meal target);
};

#endif // _DELIVERY_DRIVER_H_