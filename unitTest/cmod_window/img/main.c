#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#define ENABLE_WINDOW
#include <cmod.h>

int main() {
  fprintf(stdout, "%s,\n test for Window open.will start when you hit enter \n",
          __PRETTY_FUNCTION__);
  char d;
  scanf("%c", &d);
  fprintf(stdout, "%s,\n test for Window open.will start when you hit enter \n",
          __PRETTY_FUNCTION__);

  String *title = string_create("window test");
  Posison_data window_pont = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
  Cmod_Window *window = Cmod_Window_create(
      title, 100, 200, window_pont, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
      SDL_RENDERER_SOFTWARE);
  if (!window) {
    fprintf(stdout,
            "%s,\n this dosen't fuild at the window creating the struct \n",
            __PRETTY_FUNCTION__);
    return 1;
  }
  if (!Cmod_Window_open(window)) {
    fprintf(stdout, "%s,\n error on oping the window, fuild \n",
            __PRETTY_FUNCTION__);
    return 1;
  }
  fprintf(stdout, "%s,\n drawing a pixle to screen \n", __PRETTY_FUNCTION__);

  SDL_Event event;
  int is_runing = yes;
  while (is_runing) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        is_runing = no;
      }
    }
    Cmod_Window_draw_image(window, (Posison_data){100, 100},
                           (Cmod_Window_Rect){200, 200}, IMAGE_TYPE_BMP,
                           "./testImgage.bpm");

    Cmod_Window_flash(window);
    SDL_Delay(16);
  }
  Cmod_Window_destroy(window);
  printf("this unit test pased for the window opin");
  return 0;
}
