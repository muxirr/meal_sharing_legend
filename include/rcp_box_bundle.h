#ifndef _Rcp_BOC_BUNDLE_H_
#define _Rcp_BOC_BUNDLE_H_

#include "region.h"

class RcpBoxBundle : public Region {
public:
  RcpBoxBundle(int x, int y) : Region({x, y, 160, 88}) {}

  ~RcpBoxBundle() = default;

  void on_render(SDL_Renderer *renderer) override;
  void on_cursor_down() override;
  void on_cursor_up() override;
};

#endif // _Rcp_BOC_BUNDLE_H_