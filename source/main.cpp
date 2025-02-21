#define SDL_MAIN_HANDLED

#include "bundle.h"
#include "delivery_driver.h"
#include "microwave_oven.h"
#include "takeout_box.h"

#include "cursor_mgr.h"
#include "region_mgr.h"
#include "res_mgr.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <chrono>
#include <iostream>
#include <thread>

float fps_delta = 1.0f;
std::chrono::duration<float> delta;
const float FPS_DURATION = 1.0f; // FPS刷新间隔;

// 初始化游戏界面可交互区域;
void init_region();
// 游戏更新;
void on_update(float delta);
// 游戏渲染;
void on_render(SDL_Renderer *renderer);

int WinMain() {
  using namespace std::chrono;
  // 初始化SDL;
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
  Mix_Init(MIX_INIT_MP3);
  TTF_Init();

  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

  TTF_Font *font = TTF_OpenFont("./assets/IPix.ttf", 28);

  SDL_Window *window =
      SDL_CreateWindow("拼好饭传奇", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_ShowCursor(SDL_DISABLE);

  ResMgr::instance()->load(renderer);

  init_region();

  Mix_PlayChannel(-1, ResMgr::instance()->find_audio("bgm"), -1);

  SDL_Event event;
  bool is_quit = false;

  Timer timer_fps;
  timer_fps.set_one_shot(false);
  timer_fps.set_wait_time(FPS_DURATION);
  timer_fps.set_time_out([&] { fps_delta = delta.count(); });

  const nanoseconds frame_duration(100000000 / 144);
  steady_clock::time_point last_tick = steady_clock::now();

  while (!is_quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        is_quit = true;
        break;
      }

      CursorMgr::instance()->on_input(event);
      RegionMgr::instance()->on_input(event);
    }

    steady_clock::time_point frame_start = steady_clock::now();
    delta = frame_start - last_tick;

    on_update(delta.count());
    timer_fps.on_update(delta.count());

    SDL_RenderClear(renderer);
    on_render(renderer);

    // 显示FPS
    char fps_str[20];
    sprintf(fps_str, "FPS: %.2f", 1.0f / fps_delta);
    std::cout << fps_delta << std::endl;
    SDL_Surface *suf_fps_bg =
        TTF_RenderUTF8_Blended(font, fps_str, {55, 55, 55, 255});
    SDL_Surface *suf_fps_fg =
        TTF_RenderUTF8_Blended(font, fps_str, {255, 255, 255, 255});
    SDL_Texture *tex_fps_bg =
        SDL_CreateTextureFromSurface(renderer, suf_fps_bg);
    SDL_Texture *tex_fps_fg =
        SDL_CreateTextureFromSurface(renderer, suf_fps_fg);

    SDL_Rect rect_dst_fps = {15, 720 - suf_fps_bg->h - 15, suf_fps_bg->w,
                             suf_fps_bg->h};
    SDL_RenderCopy(renderer, tex_fps_bg, nullptr, &rect_dst_fps);
    rect_dst_fps.x -= 2;
    rect_dst_fps.y -= 2;
    SDL_RenderCopy(renderer, tex_fps_fg, nullptr, &rect_dst_fps);

    SDL_RenderPresent(renderer);

    last_tick = frame_start;
    nanoseconds sleep_duration =
        frame_duration - (steady_clock::now() - frame_start);
    if (sleep_duration > 0ns) {
      std::this_thread::sleep_for(sleep_duration);
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
}

void init_region() {
  RegionMgr::instance()->add("dalivery_driver_1", new DeliveryDriver(385, 142));
  RegionMgr::instance()->add("dalivery_driver_2", new DeliveryDriver(690, 142));
  RegionMgr::instance()->add("dalivery_driver_3", new DeliveryDriver(995, 142));

  RegionMgr::instance()->add("cola_bundle", new Bundle(300, 390, Meal::Cola));
  RegionMgr::instance()->add("sprite_bundle",
                             new Bundle(425, 390, Meal::Sprite));
  RegionMgr::instance()->add("tb_bundle",
                             new Bundle(550, 418, Meal::TakeoutBox));
  RegionMgr::instance()->add("mb_box_bundle",
                             new Bundle(225, 520, Meal::MeatBall_Box));
  RegionMgr::instance()->add("bc_box_bundle",
                             new Bundle(395, 520, Meal::BraisedChicken_Box));
  RegionMgr::instance()->add("rcp_box_bundle",
                             new Bundle(565, 520, Meal::RedCookedPork_Box));

  RegionMgr::instance()->add("microwave_oven_1", new MicrowaveOven(740, 400));
  RegionMgr::instance()->add("microwave_oven_2", new MicrowaveOven(975, 400));

  RegionMgr::instance()->add("takeout_box_1", new TakeoutBox(830, 580));
  RegionMgr::instance()->add("takeout_box_2", new TakeoutBox(935, 580));
  RegionMgr::instance()->add("takeout_box_3", new TakeoutBox(1040, 580));
  RegionMgr::instance()->add("takeout_box_4", new TakeoutBox(1145, 580));
}

void on_update(float delta) { RegionMgr::instance()->on_update(delta); }

void on_render(SDL_Renderer *renderer) {
  // 绘制背景;
  SDL_Rect rect_bg = {0, 0, 1280, 720};
  SDL_RenderCopy(renderer, ResMgr::instance()->find_texture("background"), NULL,
                 &rect_bg);

  RegionMgr::instance()->on_render(renderer);
  CursorMgr::instance()->on_render(renderer);
}