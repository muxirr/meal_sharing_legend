#ifndef _TB_BUNDLE_H_
#define _TB_BUNDLE_H_

#include "region.h"

class TbBundle : public Region {
public:
  TbBundle(int x, int y) : Region({x, y, 112, 96}) {}

  ~TbBundle() = default;

  void on_render(SDL_Renderer *renderer) override;
  void on_cursor_down() override;
  void on_cursor_up() override;
};

#endif // _TB_BUNDLE_H_