#define SDL_MAIN_HANDLED

#include "cursor_mgr.h"
#include "res_mgr.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

int WinMain() {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  Mix_Init(MIX_INIT_MP3);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

  return 0;
}