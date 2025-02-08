#ifndef _SPRITE_BUNDLE_H_
#define _SPRITE_BUNDLE_H_

#include "region.h"

class SpriteBundle : public Region {
public:
  SpriteBundle(int x, int y) : Region({x, y, 120, 124}) {}

  ~SpriteBundle() = default;

  void on_render(SDL_Renderer *renderer) override;
  void on_cursor_down() override;
  void on_cursor_up() override;
};

#endif // _SPRITE_BUNDLE_H_