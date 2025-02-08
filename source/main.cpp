#define SDL_MAIN_HANDLED

#include "bundle.h"

#include "cursor_mgr.h"
#include "region_mgr.h"
#include "res_mgr.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

int WinMain() {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  Mix_Init(MIX_INIT_MP3);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

  SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, 800, 600, 0);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Event event;
  ResMgr::instance()->load(renderer);
  RegionMgr::instance()->add("cola_bundle", new Bundle(100, 100, Meal::Cola));
  RegionMgr::instance()->add("bc_box_bundle",
                             new Bundle(300, 100, Meal::BraisedChicken_Box));
  RegionMgr::instance()->add("mb_box_bundle",
                             new Bundle(500, 100, Meal::MeatBall_Box));
  RegionMgr::instance()->add("rcp_box_bundle",
                             new Bundle(100, 300, Meal::RedCookedPork_Box));
  RegionMgr::instance()->add("sprite_bundle",
                             new Bundle(300, 300, Meal::Sprite));
  RegionMgr::instance()->add("tb_bundle",
                             new Bundle(500, 300, Meal::TakeoutBox));
  SDL_ShowCursor(SDL_DISABLE);
  Mix_Music *music = Mix_LoadMUS("./assets/audio/bgm.mp3");
  Mix_PlayMusic(music, -1);
  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return 0;
      } else {
        RegionMgr::instance()->on_input(event);
        CursorMgr::instance()->on_input(event);
      }
    }
    SDL_RenderClear(renderer);
    RegionMgr::instance()->on_render(renderer);
    CursorMgr::instance()->on_render(renderer);
    SDL_RenderPresent(renderer);
  }
  return 0;
}