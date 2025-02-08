#ifndef _BC_BOC_BUNDLE_H_
#define _BC_BOC_BUNDLE_H_

#include "region.h"

class BcBoxBundle : public Region {
public:
  BcBoxBundle(int x, int y) : Region({x, y, 160, 88}) {}

  ~BcBoxBundle() = default;

  void on_render(SDL_Renderer *renderer) override;
  void on_cursor_down() override;
  void on_cursor_up() override;
};

#endif // _BC_BOC_BUNDLE_H_