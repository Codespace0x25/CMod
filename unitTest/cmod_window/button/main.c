#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string.h>
#define ENABLE_WINDOW
#include <cmod.h>

int clickamoutn = 0;
void onClick() { INC clickamoutn; }

int is_point_inside_rect(int x, int y, Cmod_Window_Button *button) {
  return (x >= button->pos.x && x <= button->pos.x + button->rect.w &&
          y >= button->pos.y && y <= button->pos.y + button->rect.h);
}

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
  String *button_text = string_create("click me");
  Posison_data point = {100, 100};
  Cmod_Window_Color color = {23, 255, 23, 100};
  Cmod_Window_Color color2 = {23, 23, 23, 100};
  Cmod_Window_Color color3 = {255, 255, 255, 100};
  Cmod_Window_Rect rect = {200, 100};

  Posison_data pointF = {200, 100};
  Cmod_Window_Button *button = Cmod_Window_button_create(
      window, point, rect, color, color2, 25, color3,
      (Path_t) "/usr/share/fonts/TTF/BigBlueTerm437NerdFont-Regular.ttf", 25,
      button_text, onClick);
  int is_runing = yes;
  SDL_Event event;
  while (is_runing) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        is_runing = no;
      }
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          int mouseX = event.button.x;
          int mouseY = event.button.y;

          if (is_point_inside_rect(mouseX, mouseY, button)) {
            button->onClick();
          }
        }
      }
    }
    char num[100];
    sprintf(num, "%d", clickamoutn);
    String counter = {num, strlen(num)};
    Cmod_Window_draw_text(
        window, (Posison_data){50, 50}, color3,
        (Path_t) "/usr/share/fonts/TTF/BigBlueTerm437NerdFont-Regular.ttf", 25,
        &counter);
    Cmod_Window_button_draw(button);
    Cmod_Window_flash(window);
    SDL_Delay(16);
  }
  string_destroy(button_text);
  Cmod_Window_button_destroy(button);
  Cmod_Window_destroy(window);
  printf("this unit test pased for the window opin");
  return 0;
}
