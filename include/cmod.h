#pragma once
// ============================= INCLUDES ===========================
//
// why... would you do this. this is supost to be small.
// this is beacse i dont want to have to build it my self
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
// what would you do this that make a less poetable
//
//
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// ============================ TYPES =============================

typedef unsigned int Uint;

// the deconstructer for a object
typedef void Deleter;

// a general pointer
typedef void *Pointer_t;
typedef char *Path_t; // that is this... oOo its a file path to make a the end
                      // user better... ok

// A situation or surrounding substance within which something else originates,
// develops, or is contained.
typedef struct Matrix {
  float **data;
  size_t rows;
  size_t cols;
} Matrix;

// string do i have to say any thang else
typedef struct String {
  char *data;
  size_t length;
} String;
// types of http reqruest;
typedef enum { GET, POST, PUT, DELETE } RequestType;
// this is to be a binamic list for a way to srotr a orderd list that you would
// like to be fist in fist out.

typedef struct {
  size_t back, fround, size;
  char **data;
} Queue_t;

// ======================== HASH NODE =========================
typedef struct HashNode {
  char *key;
  void *value; // Pointer to any type of value
  struct HashNode *next;
} HashNode;

// ======================== HASH TABLE =========================
typedef struct {
  size_t size;
  size_t count;
  HashNode **buckets;
} HashTable;

typedef struct {
  int x, y;
} Posison_data;

// why is ther alot of commeints there. we can all gest by your  shten
// and hay do you use
typedef struct {
  SDL_Window *window;   // pointer to the window type
  SDL_Renderer *render; // the renderer to draw to screen
  String *title;        // to be used as a window title
  SDL_Event event;      // to get events to interact with
  Uint width, height;   // size size of the window
  Posison_data pos;
  Uint32 sdl_window_flags;
  Uint32 sdl_render_flags;
} Cmod_Window;
typedef SDL_Color Cmod_Window_Color;
typedef struct {
  int w, h;
} Cmod_Window_Rect;
typedef struct {
  Cmod_Window *window;
  Posison_data pos;
  Cmod_Window_Rect rect;
  Cmod_Window_Color backgraound;
  Cmod_Window_Color border;
  uint thickness;
  Cmod_Window_Color text_color;
  Path_t font_path;
  int font_size;
  String *text;
  void (*onClick)();
} Cmod_Window_Button;

typedef enum {
  IMAGE_TYPE_UNKNOWN,
  IMAGE_TYPE_PNG,
  IMAGE_TYPE_JPG,
  IMAGE_TYPE_BMP,
  //  IMAGE_TYPE_GIF, // im not doing this rite now as this seems like it would
  //  be hard, but if i ever need it ill inplment it
  IMAGE_TYPE_TGA,
  //  IMAGE_TYPE_SVG, // i may do this
  //  IMAGE_TYPE_MEMORY // i see no reson for this.
} ImageType;

// =========================== DEFINITION ==========================
#define OR |
#define no 0
#define AND &
#define yes 1
#define IS ==
#define INC ++
#define DEC --
#define L_OR ||
#define maybe 2
#define L_AND &&
#define IS_AT ->
#define MODULO %
#define IS_NOT !=
#define DEC_BY -=
#define WILL_BE =
#define INC_BY +=
#define LESS_THAN <
#define SHIFT_LEFT <<
#define SHIFT_RIGHT >>
#define PI 3.141592653
#define GREATER_THAN >
#define LESS_THAN_OR_EQUAL <=
#define GREATER_THAN_OR_EQUAL >=
#define MUST_BE_FREE [[nodiscard]]

// ========================== MATRIX API ==========================
#ifdef ENABLE_MATRIX
Matrix *matrix_create(size_t rows, size_t cols);

Deleter matrix_destroy(Matrix *m);

Matrix *matrix_add(const Matrix *a, const Matrix *b);

Matrix *matrix_sub(const Matrix *a, const Matrix *b);

Matrix *matrix_mul(const Matrix *a, const Matrix *b);

Matrix *matrix_div(const Matrix *a, const Matrix *b);

#endif
// ========================== STRING API ==========================
#ifndef DISABEL_STRING

String *string_create(const char *initial_data);

Deleter string_destroy(String *s);

void string_replace(String *s, const char *find, const char *replace);

String *string_find(const String *s, const char *substring);

void pprintf(const char *format, ...);

#endif

#define Make_String(name, data) (String *name = string_create(data))
#define To_char(input) (input->data)

// ========================== FILE API ===========================
#ifdef ENABLE_FILE
void write_file(String filepath, String *input);

String *read_file(String filepast);
#endif
// ========================== HTTP API ===========================
#ifdef ENABLE_HTTP
String *http_request(RequestType type, String *url, String *headers,
                     String *body);
#endif
// ========================== QUEUE API =======================
#ifdef ENABLE_QUEUE

MUST_BE_FREE Queue_t *queue_create();
void queue_destroyer(Queue_t *queue);
void queue_add(Queue_t *queue, char *data);
char *queue_pull(Queue_t *queue);
#endif
// ========================== HASH MAP API ======================

#ifdef ENABLE_HASH_MAP
HashTable *hash_table_create(size_t size);
void hash_table_destroy(HashTable *table);
void hash_table_insert(HashTable *table, const char *key, void *value);
void *hash_table_get(HashTable *table, const char *key);
void hash_table_remove(HashTable *table, const char *key);
void hash_table_resize(HashTable *table, size_t new_size);
Uint hash_function(const char *key, size_t size);
#endif

#ifdef ENABLE_WINDOW
MUST_BE_FREE Cmod_Window *Cmod_Window_create(String *title, Uint width,
                                             Uint height, Posison_data pos,
                                             Uint32 sdl_window_flags,
                                             Uint32 sdl_render_flags);

void Cmod_Window_destroy(Cmod_Window *window);
int Cmod_Window_open(Cmod_Window *window);
void Cmod_Window_flash(Cmod_Window *window);
void Cmod_Window_draw_pixle(Cmod_Window *window, Cmod_Window_Color color,
                            Posison_data pos);
void Cmod_Window_draw_rect(Cmod_Window *window, Cmod_Window_Color color,
                           Posison_data pos, Cmod_Window_Rect rect,
                           uint thickness);
void Cmod_Window_draw_rect_fill(Cmod_Window *window, Cmod_Window_Color color,
                                Posison_data pos, Cmod_Window_Rect rect);
void Cmod_Window_draw_circle(Cmod_Window *window, Cmod_Window_Color color,
                             Posison_data pos, uint32_t radius, uint thickness);
void Cmod_Window_draw_circle_fill(Cmod_Window *window, Cmod_Window_Color color,
                                  Posison_data pos, uint32_t radius);

/*
 * this was a good try but yor types where.
 */

// and also what is this TOOL_KIT.
// this is so we can have a ui lib build in for eazy acsess to stuff.
// but what if you dont need teh Cmod button ro text

Cmod_Window_Button *
Cmod_Window_button_create(Cmod_Window *window, Posison_data pos,
                          Cmod_Window_Rect rect, Cmod_Window_Color backgraound,
                          Cmod_Window_Color border, uint thickness,
                          Cmod_Window_Color text_color, Path_t font_path,
                          int font_size, String *text, void (*onClick)());
void Cmod_Window_draw_text(Cmod_Window *window, Posison_data pos,
                           Cmod_Window_Color color, Path_t font_path,
                           int font_size, String *test);
void Cmod_Window_button_draw(Cmod_Window_Button *button);
void Cmod_Window_button_destroy(Cmod_Window_Button *button);

// image.

void Cmod_Window_Draw_image(Cmod_Window *window, Posison_data pos,
                            Cmod_Window_Rect rect, ImageType image_type,
                            Path_t file);
#endif
