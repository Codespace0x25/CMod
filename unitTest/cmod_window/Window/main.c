#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#define ENABLE_WINDOW
#include <cmod.h>

int main() {
  String *logs = string_create("");
  fprintf(stdout, "%s,\n test for Window open.will start when you hit enter \n",
          __PRETTY_FUNCTION__);
  scanf("");
  fprintf(stdout, "%s,\n test for Window open.will start when you hit enter \n",
          __PRETTY_FUNCTION__);

  String *title = string_create("window test");
  Posison_data window_pont = {NULL, NULL};
  Cmod_Window *window = Cmod_Window_create(
      title, 100, 200, window_pont, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
      SDL_RENDERER_SOFTWARE);
  if (!window) {

    return 0;
  }
}
