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
  Posison_data point = {500, 500};
  Posison_data point2 = {750, 500};
  Cmod_Window_Color color = {255, 255, 255, 100};
  Cmod_Window_Color color2 = {0, 255, 160, 100};
  Cmod_Window_Color color3 = {0, 0, 0, 100};
  Cmod_Window_Color color4 = {255, 164, 203, 100};
  Cmod_Window_Color color4s = {255, 122, 160, 100};
  Cmod_Window_Color color4m = {78, 9, 22, 100};
  Cmod_Window_Color color4t = {255, 255, 255, 100};
  String *string = string_create("his name is jon");

  Posison_data pointF = {200, 100};
  Cmod_Window_Color colorF = {255, 0, 255, 100};
  Cmod_Window_Rect rectF = {600, 500};
  Cmod_Window_Rect rectFs = {200, 500};
  Cmod_Window_Rect Mouth = {200, 100};
  Cmod_Window_Rect teath = {200, 20};
  Cmod_Window_Rect brow = {200, 50};
  int is_runing = yes;
  SDL_Event event;
  while (is_runing) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        is_runing = no;
      }
    }
    Cmod_Window_draw_rect_fill(window, color4, (Posison_data){250, 300}, rectF);
    Cmod_Window_draw_rect_fill(window, color4s, (Posison_data){250, 300},
                               rectFs);
    Cmod_Window_draw_rect_fill(window, color4m, (Posison_data){570, 660},
                               Mouth);
    Cmod_Window_draw_rect_fill(window, color4t, (Posison_data){570, 660},
                               teath);
    Cmod_Window_draw_rect_fill(window, color4t, (Posison_data){570, 750},
                               teath);
    Cmod_Window_draw_rect_fill(window, color4m, (Posison_data){450, 350}, brow);
    Cmod_Window_draw_rect_fill(window, color4m, (Posison_data){450 * 1.5, 350},
                               brow);
    Cmod_Window_draw_circle_fill(window, color, point, 100);
    Cmod_Window_draw_circle_fill(window, color2, point, 50);
    Cmod_Window_draw_circle_fill(window, color3, point, 23);
    Cmod_Window_draw_circle_fill(window, color, point2, 100);
    Cmod_Window_draw_circle_fill(window, color2, point2, 50);
    Cmod_Window_draw_circle_fill(window, color3, point2, 23);
    Cmod_Window_draw_text(
        window, (Posison_data){200, 200},
        (Cmod_Window_Color){255, 255, 255, 100},
        (Path_t) "/usr/share/fonts/TTF/BigBlueTerm437NerdFont-Regular.ttf", 50,
        string);
    Cmod_Window_flash(window);
    SDL_Delay(16);
  }
  Cmod_Window_destroy(window);
  printf("this unit test pased for the window opin");
  return 0;
}
