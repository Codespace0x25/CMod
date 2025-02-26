#include "../include/cmod.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========================== MATRIX API ==========================

/**
 * @brief Create a matrix with the specified number of rows and columns.
 *
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 * @return Pointer to the created Matrix, or NULL if allocation fails.
 */
Matrix *matrix_create(size_t rows, size_t cols) {
  Matrix *m = (Matrix *)malloc(sizeof(Matrix));
  m->rows = rows;
  m->cols = cols;
  m->data = (float **)malloc(rows * sizeof(float *));
  for (size_t i = 0; i < rows; i++) {
    m->data[i] = (float *)calloc(cols, sizeof(float));
  }
  return m;
}
/**
 * @brief Free the memory associated with a Matrix object.
 *
 * @param m Pointer to the Matrix to be destroyed. Does nothing if NULL.
 */
void matrix_destroy(Matrix *m) {
  if (m) {
    for (size_t i = 0; i < m->rows; i++) {
      free(m->data[i]);
    }
    free(m->data);
    free(m);
  }
}
/**
 * @brief Add two matrices.
 *
 * @param a Pointer to the first matrix.
 * @param b Pointer to the second matrix.
 * @return Pointer to the resulting Matrix, or NULL if dimensions mismatch.
 */
Matrix *matrix_add(const Matrix *a, const Matrix *b) {
  if (a->rows != b->rows || a->cols != b->cols)
    return NULL;

  Matrix *result = matrix_create(a->rows, a->cols);
  for (size_t i = 0; i < a->rows; i++) {
    for (size_t j = 0; j < a->cols; j++) {
      result->data[i][j] = a->data[i][j] + b->data[i][j];
    }
  }
  return result;
}
/**
 * @brief Subtract matrix b from matrix a.
 *
 * @param a Pointer to the first matrix.
 * @param b Pointer to the second matrix.
 * @return Pointer to the resulting Matrix, or NULL if dimensions mismatch.
 */
Matrix *matrix_sub(const Matrix *a, const Matrix *b) {
  if (a->rows != b->rows || a->cols != b->cols)
    return NULL;
  Matrix *result = matrix_create(a->rows, a->cols);
  for (size_t i = 0; i < a->rows; i++) {
    for (size_t j = 0; j < a->cols; j++) {
      result->data[i][j] = a->data[i][j] - b->data[i][j];
    }
  }
  return result;
}
Matrix *matrix_mul(const Matrix *a, const Matrix *b) {
  if (a->cols IS_NOT b->rows)
    return NULL;
  Matrix *result = matrix_create(a->rows, b->cols);
  for (size_t i = 0; i < a->rows; i++) {
    for (size_t j = 0; j < b->cols; j++) {
      result->data[i][j] = 0;
      for (size_t k = 0; k < a->cols; k++) {
        result->data[i][j] += a->data[i][k] * b->data[k][j];
      }
    }
  }
  return result;
}
Matrix *matrix_div(const Matrix *a, const Matrix *b) {
  if (a->rows IS_NOT b->rows L_OR a->cols IS_NOT b->cols)
    return NULL;
  Matrix *result = matrix_create(a->rows, a->cols);
  for (size_t i = 0; i < a->rows; i++) {
    for (size_t j = 0; j < a->cols; j++) {
      if (b->data[i][j] != 0) {
        result->data[i][j] = a->data[i][j] / b->data[i][j];
      } else {
        result->data[i][j] = 0;
        fprintf(stderr,
                "you souldint do this you are deviding by a 0. that is bad");
      }
    }
  }
  return result;
}
// ========================== STRING API ==========================

/**
 * @brief Create a new String object with the given initial data.
 *
 * @param initial_data C-string to initialize the String object with.
 * @return Pointer to the created String, or NULL if allocation fails.
 */
String *string_create(const char *initial_data) {
  size_t len = strlen(initial_data);
  String *s = (String *)malloc(sizeof(String));
  s->data = (char *)malloc((len + 1) * sizeof(char));
  strcpy(s->data, initial_data);
  s->length = len;
  return s;
}
/**
 * @brief Free the memory associated with a String object.
 *
 * @param s Pointer to the String to be destroyed. Does nothing if NULL.
 */
void string_destroy(String *s) {
  if (s) {
    free(s->data);
    free(s);
  }
}

/**
 * @brief Replace occurrences of a substring with another string within a String
 * object.
 *
 * @param s Pointer to the String object.
 * @param find Substring to find.
 * @param replace Substring to replace it with.
 */
void string_replace(String *s, const char *find, const char *replace) {
  char *pos = strstr(s->data, find);
  if (!pos)
    return;
  size_t find_len = strlen(find);
  size_t replace_len = strlen(replace);
  size_t new_len = s->length - find_len + replace_len;
  char *new_data = (char *)malloc(new_len + 1);
  strncpy(new_data, s->data, pos - s->data);
  new_data[pos - s->data] = '\0';
  strcat(new_data, replace);
  strcat(new_data, pos + find_len);
  free(s->data);
  s->data = new_data;
  s->length = new_len;
}

// ========================== HTTP API =========================== #include
// <curl/curl.h> /** * @brief Callback function for libcurl to handle response
// data. * * @param ptr Pointer to the response data. * @param size Size of each
// data chunk.
*@param nmemb Number of data chunks
        .*@param userdata Pointer to the String object storing the
            response.*@ return Number of bytes handled.*
    /
    static size_t write_callback(void *ptr, size_t size, size_t nmemb,
                                 void *userdata) {
  size_t total_size = size * nmemb;
  String *response = (String *)userdata;
  response->data =
      (char *)realloc(response->data, response->length + total_size + 1);
  memcpy(response->data + response->length, ptr, total_size);
  response->length += total_size;
  response->data[response->length] = '\0';
  return total_size;
}

/**
 * @brief Perform an HTTP request using libcurl.
 *
 * @param type Type of the HTTP request (GET, POST, PUT, DELETE).
 * @param url Pointer to the URL String object.
 * @param headers Pointer to the headers String object (newline-separated).
 * @param body Pointer to the body String object for POST/PUT requests.
 * @return Pointer to the response String object, or NULL on failure.
 */
String *http_request(RequestType type, String *url, String *headers,
                     String *body) {
  CURL *curl = curl_easy_init();
  if (!curl)
    return NULL;
  CURLcode res;
  String *response = (String *)malloc(sizeof(String));
  response->data = (char *)malloc(1);
  response->data[0] = '\0';
  response->length = 0;
  struct curl_slist *curl_headers = NULL;
  if (headers) {
    char *header_copy = strdup(headers->data);
    char *line = strtok(header_copy, "\n");
    while (line) {
      curl_headers = curl_slist_append(curl_headers, line);
      line = strtok(NULL, "\n");
    }
    free(header_copy);
  }
  curl_easy_setopt(curl, CURLOPT_URL, url->data);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
  if (type == POST || type == PUT) {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body ? body->data : "");
  }
  if (type == PUT) {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
  }
  if (type == DELETE) {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
  }
  if (curl_headers) {
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
  }
  res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    fprintf(stderr, "HTTP request failed: %s\n", curl_easy_strerror(res));
    string_destroy(response);
    response = NULL;
  }
  curl_slist_free_all(curl_headers);
  curl_easy_cleanup(curl);
  return response;
}
// ========================== FILE PROSESES =======================
String *read_file(String filepast) {
  String *timp = string_create("");
  FILE *file = fopen(filepast.data, "rb");
  if (!file) {
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  rewind(file);
  char *buffer = (char *)malloc(length + 1);
  if (!buffer) {
    fclose(file);
    return NULL;
  }
  fread(buffer, 1, length, file);
  buffer[length] = '\0';
  timp->length = length;
  timp->data = (char *)&buffer;
  fclose(file);
  return timp;
}
void write_file(String filepath, String *input) {
  FILE *file = fopen(filepath.data, "rb");
  if (!file) {
    fputs("error: unable to open the file check if you have premishon", stderr);
    return;
  }
  fprintf(file, "%s", To_char(input));
  fclose(file);
}
// ========================== CUSTOM PRINTF =======================
/**
 * @brief A custom printf function supporting String objects.
 *
 * @param format Format string, with `%s` to print String objects.
 * @param ... Additional arguments for the format string.
 */
void pprintf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  const char *ptr = format;
  while (*ptr) {
    if (*ptr == '%' && *(ptr + 1) == 's') {
      String *s = va_arg(args, String *);
      printf("%s", To_char(s));
      ptr++;
    } else {
      putchar(*ptr);
    }
    ptr++;
  }
  va_end(args);
}

// ========================== LIST API =======================
#define INITIAL_SIZE 4
MUST_BE_FREE Queue_t *queue_create() {
  Queue_t *queue = (Queue_t *)malloc(sizeof(Queue_t));
  if (!queue)
    return NULL;
  queue->size = INITIAL_SIZE;
  queue->fround = 0;
  queue->back = 0;
  queue->data = (char **)malloc(queue->size * sizeof(char *));
  if (!queue->data) {
    free(queue);
    return NULL;
  }
  return queue;
}
void queue_destroyer(Queue_t *queue) {
  if (!queue)
    return;
  free(queue->data);
  free(queue);
}
void queue_add(Queue_t *queue, char *data) {
  if (queue->fround >= queue->size) {
    queue->size *= 2;
    queue->data = (char **)realloc(queue->data, queue->size * sizeof(char *));
    if (!queue->data)
      return;
  }

  queue->data[queue->fround++] = data;
}

char *queue_pull(Queue_t *queue) {
  if (queue->back == queue->fround)
    return NULL;
  return queue->data[queue->back++];
}

// ======================== HASH FUNCTION =========================
uint hash_function(const char *key, size_t size) {
  uint hash_value = 0;
  for (size_t i = 0; key[i] != '\0'; i++) {
    hash_value += key[i];
    hash_value = (hash_value * 31) % size;
  }
  return hash_value;
}

// ======================== CREATE HASH TABLE =========================
HashTable *hash_table_create(size_t size) {
  HashTable *table = malloc(sizeof(HashTable));
  if (table == NULL)
    return NULL;

  table->size = size;
  table->count = 0;
  table->buckets = calloc(size, sizeof(HashNode *));

  return table;
}
// Declare the hash_table_resize function before it's used
void hash_table_resize(HashTable *table, size_t new_size);
// ======================== INSERT INTO HASH TABLE =========================
void hash_table_insert(HashTable *table, const char *key, Pointer_t value) {
  uint index = hash_function(key, table->size);
  HashNode *new_node = malloc(sizeof(HashNode));

  if (new_node == NULL)
    return;

  new_node->key = strdup(key);
  new_node->value = value;
  new_node->next = table->buckets[index];
  table->buckets[index] = new_node;
  table->count++;

  // Resize if load factor exceeds 75%
  if ((table->count * 100) > (table->size * 75)) {
    hash_table_resize(table, table->size * 2);
  }
}

// ======================== GET FROM HASH TABLE =========================
Pointer_t hash_table_get(HashTable *table, const char *key) {
  uint index = hash_function(key, table->size);
  HashNode *node = table->buckets[index];

  while (node != NULL) {
    if (strcmp(node->key, key) == 0)
      return node->value;
    node = node->next;
  }
  return NULL;
}

// ======================== REMOVE FROM HASH TABLE =========================
void hash_table_remove(HashTable *table, const char *key) {
  uint index = hash_function(key, table->size);
  HashNode *node = table->buckets[index];
  HashNode *prev = NULL;

  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      if (prev == NULL) {
        table->buckets[index] = node->next;
      } else {
        prev->next = node->next;
      }

      free(node->key);
      free(node);
      table->count--;
      return;
    }
    prev = node;
    node = node->next;
  }
}

// ======================== DESTROY HASH TABLE =========================
void hash_table_destroy(HashTable *table) {
  for (size_t i = 0; i < table->size; i++) {
    HashNode *node = table->buckets[i];
    while (node != NULL) {
      HashNode *temp = node;
      node = node->next;

      free(temp->key);
      free(temp);
    }
  }
  free(table->buckets);
  free(table);
}

void hash_table_resize(HashTable *table, size_t new_size) {
  HashTable *new_table = hash_table_create(new_size);
  if (new_table == NULL)
    return;

  for (size_t i = 0; i < table->size; i++) {
    HashNode *node = table->buckets[i];
    while (node != NULL) {
      hash_table_insert(new_table, node->key, node->value);
      node = node->next;
    }
  }

  HashNode **old_buckets = table->buckets;
  table->buckets = new_table->buckets;
  table->size = new_table->size;
  table->count = new_table->count;

  free(old_buckets);
  free(new_table);
}

static Cmod_Window_Color default_draw_color = {0, 0, 0, 100};

MUST_BE_FREE Cmod_Window *Cmod_Window_create(String *title, Uint width,
                                             Uint height, Posison_data pos,
                                             Uint32 sdl_window_flags,
                                             Uint32 sdl_render_flags) {
  if (0 IS_NOT SDL_Init(SDL_INIT_EVERYTHING))
    return NULL;
  if (-1 IS TTF_Init())
    return NULL;
  if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)
            AND(IMG_INIT_JPG | IMG_INIT_PNG))) {
    return NULL;
  }
  Cmod_Window *timp = (Cmod_Window *)malloc(sizeof(Cmod_Window));
  if (!timp)
    return 0;
  timp->title = title;
  timp->width = width;
  timp->height = height;
  timp->pos = pos;
  timp->sdl_window_flags = sdl_window_flags;
  timp->sdl_render_flags = sdl_render_flags;
  return timp;
}

void Cmod_Window_destroy(Cmod_Window *window) {
  SDL_DestroyWindow(window->window);
  SDL_DestroyRenderer(window->render);
  SDL_Quit();
  free(window->title);
  free(window);
}

int Cmod_Window_open(Cmod_Window *window) {
  window->window =
      SDL_CreateWindow(To_char(window->title), window->pos.x, window->pos.y,
                       window->width, window->height, window->sdl_window_flags);
  if (!window->window)
    return no;
  window->render =
      SDL_CreateRenderer(window->window, -1, window->sdl_render_flags);
  if (!window->render) {
    SDL_DestroyWindow(window->window);
    return no;
  }

  return yes;
}

void Cmod_Window_set_default_draw_color(Cmod_Window *window,
                                        Cmod_Window_Color color) {
  default_draw_color = color;
  SDL_SetRenderDrawColor(window->render, color.r, color.b, color.g, color.a);
}
void Cmod_Window_default_load_draw_color(Cmod_Window *window) {
  SDL_SetRenderDrawColor(window->render, default_draw_color.r,
                         default_draw_color.b, default_draw_color.g,
                         default_draw_color.a);
}
void Cmod_Window_set_color(Cmod_Window *window, Cmod_Window_Color color) {
  SDL_SetRenderDrawColor(window->render, color.r, color.b, color.g, color.a);
}

void Cmod_Window_flash(Cmod_Window *window) {
  SDL_RenderPresent(window->render);
  SDL_RenderClear(window->render);
}
void Cmod_Window_draw_pixle(Cmod_Window *window, Cmod_Window_Color color,
                            Posison_data pos) {
  Cmod_Window_set_color(window, color);
  SDL_RenderDrawPoint(window->render, pos.x, pos.y);
  Cmod_Window_default_load_draw_color(window);
}
void Cmod_Window_draw_rect(Cmod_Window *window, Cmod_Window_Color color,
                           Posison_data pos, Cmod_Window_Rect rect,
                           uint thickness) {
  for (int i WILL_BE no; i IS_NOT rect.w; INC i) {
    for (Uint j WILL_BE no; j IS_NOT thickness; INC j) {
      Posison_data top_pixel WILL_BE{i + pos.x, j + pos.y};
      Cmod_Window_draw_pixle(window, color, top_pixel);
      int bottom_y WILL_BE pos.y + rect.h;
      bottom_y DEC_BY thickness;
      bottom_y DEC_BY yes;
      Posison_data bottom_pixel WILL_BE{i + pos.x, bottom_y + j};
      Cmod_Window_draw_pixle(window, color, bottom_pixel);
    }
  }

  for (int i WILL_BE no; i IS_NOT rect.h; INC i) {
    for (Uint j WILL_BE no; j IS_NOT thickness; INC j) {
      Posison_data left_pixel WILL_BE{pos.x + j, i + pos.y};
      Cmod_Window_draw_pixle(window, color, left_pixel);
      int right_x WILL_BE pos.x + rect.w;
      right_x DEC_BY thickness;
      right_x DEC_BY yes;
      Posison_data right_pixel WILL_BE{right_x + j, i + pos.y};
      Cmod_Window_draw_pixle(window, color, right_pixel);
    }
  }
}
void Cmod_Window_draw_rect_fill(Cmod_Window *window, Cmod_Window_Color color,
                                Posison_data pos, Cmod_Window_Rect rect) {
  for (int i WILL_BE 0; i IS_NOT rect.w; INC i) {
    for (int j WILL_BE 0; j IS_NOT rect.h; INC j) {
      Posison_data timp WILL_BE{pos.x + i, j + pos.y};
      Cmod_Window_draw_pixle(window, color, timp);
    }
  }
}
void Cmod_Window_draw_hline(Cmod_Window *window, Cmod_Window_Color color,
                            int x1, int x2, int y) {
  for (int x = x1; x <= x2; x++) {
    Cmod_Window_draw_pixle(window, color, (Posison_data){x, y});
  }
}

void Cmod_Window_draw_circle(Cmod_Window *window, Cmod_Window_Color color,
                             Posison_data pos, uint32_t radius,
                             uint thickness) {
  int cx = pos.x, cy = pos.y;

  for (uint t = 0; t < thickness; t++) { // Loop for thickness
    int r = radius - t;
    int x = 0, y = r;
    int d = 1 - r;

    while (y >= x) {
      // Plot pixels in all 8 octants
      Cmod_Window_draw_pixle(window, color, (Posison_data){cx + x, cy + y});
      Cmod_Window_draw_pixle(window, color, (Posison_data){cx - x, cy + y});
      Cmod_Window_draw_pixle(window, color, (Posison_data){cx + x, cy - y});
      Cmod_Window_draw_pixle(window, color, (Posison_data){cx - x, cy - y});
      Cmod_Window_draw_pixle(window, color, (Posison_data){cx + y, cy + x});
      Cmod_Window_draw_pixle(window, color, (Posison_data){cx - y, cy + x});
      Cmod_Window_draw_pixle(window, color, (Posison_data){cx + y, cy - x});
      Cmod_Window_draw_pixle(window, color, (Posison_data){cx - y, cy - x});

      x++;
      if (d < 0) {
        d += 2 * x + 1;
      } else {
        y--;
        d += 2 * (x - y) + 1;
      }
    }
  }
}
void Cmod_Window_draw_circle_fill(Cmod_Window *window, Cmod_Window_Color color,
                                  Posison_data pos, uint32_t radius) {
  int cx = pos.x, cy = pos.y;
  int x = 0, y = radius;
  int d = 1 - radius;

  // Draw initial center line
  Cmod_Window_draw_hline(window, color, cx - radius, cx + radius, cy);

  while (y >= x) {
    // Draw horizontal scanlines to fill the circle
    Cmod_Window_draw_hline(window, color, cx - x, cx + x, cy - y);
    Cmod_Window_draw_hline(window, color, cx - x, cx + x, cy + y);
    Cmod_Window_draw_hline(window, color, cx - y, cx + y, cy - x);
    Cmod_Window_draw_hline(window, color, cx - y, cx + y, cy + x);

    x++;
    if (d < 0) {
      d += 2 * x + 1;
    } else {
      y--;
      d += 2 * (x - y) + 1;
    }
  }
}

void Cmod_Window_draw_text(Cmod_Window *window, Posison_data pos,
                           Cmod_Window_Color color, Path_t font_path,
                           int font_size, String *test) {
  TTF_Font *font = TTF_OpenFont(font_path, font_size);
  if (!font) {
    printf("TTF_OpenFont error: %s\n", TTF_GetError());
    return;
  }
  SDL_Surface *text_surface = TTF_RenderText_Solid(font, To_char(test), color);
  if (!text_surface) {
    printf("TTF_RenderText_Solid error: %s\n", TTF_GetError());
    TTF_CloseFont(font);
    return;
  }
  SDL_Texture *text_Texture =
      SDL_CreateTextureFromSurface(window->render, text_surface);
  if (!text_Texture) {
    printf("SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    return;
  }
  SDL_Rect dst_rect = {pos.x, pos.y, text_surface->w, text_surface->h};
  SDL_RenderCopy(window->render, text_Texture, NULL, &dst_rect);
  SDL_DestroyTexture(text_Texture);
  SDL_FreeSurface(text_surface);
  TTF_CloseFont(font);
}

Cmod_Window_Button *
Cmod_Window_button_create(Cmod_Window *window, Posison_data pos,
                          Cmod_Window_Rect rect, Cmod_Window_Color backgraound,
                          Cmod_Window_Color border, uint thickness,
                          Cmod_Window_Color text_color, Path_t font_path,
                          int font_size, String *text, void (*onClick)()) {
  Cmod_Window_Button *timp =
      (Cmod_Window_Button *)malloc(sizeof(Cmod_Window_Button));
  if (!timp) {
    fprintf(stderr, "%s, error constructing a button", __FUNCTION__);
  }
  timp->window = window;
  timp->pos = pos;
  timp->rect = rect;
  timp->backgraound = backgraound;
  timp->border = border;
  timp->thickness = thickness;
  timp->text_color = text_color;
  timp->font_path = font_path;
  timp->font_size = font_size;
  timp->text = text;
  timp->onClick = onClick;
  return timp;
}
void Cmod_Window_button_destroy(Cmod_Window_Button *button) { free(button); }

void Cmod_Window_button_draw(Cmod_Window_Button *button) {
  if (!button) {
    fprintf(
        stderr,
        "%s - you can't draw a NULL button, so check the button if its NULL",
        __FUNCTION__);
    return;
  }
  Cmod_Window_draw_rect_fill(button->window, button->backgraound, button->pos,
                             button->rect);
  Cmod_Window_draw_rect(button->window, button->border, button->pos,
                        button->rect, button->thickness);

  Cmod_Window_draw_text(
      button->window,
      (Posison_data){(button->pos.x + button->rect.w / 3) - button->font_size +
                         button->text->length / 3,
                     (button->pos.y + button->rect.h / 3)},
      button->text_color, button->font_path, button->font_size, button->text);
}

// this should never be exposed as this si to help with errors of not knowing
// the image type.
ImageType detect_image_type(const char *filename) {
  const char *ext = strrchr(filename, '.');
  if (!ext)
    return IMAGE_TYPE_UNKNOWN;
  ext++; // Move past the dot

  if (strcasecmp(ext, "png") == 0)
    return IMAGE_TYPE_PNG;
  if (strcasecmp(ext, "jpg") == 0 || strcasecmp(ext, "jpeg") == 0)
    return IMAGE_TYPE_JPG;
  if (strcasecmp(ext, "bmp") == 0)
    return IMAGE_TYPE_BMP;
  if (strcasecmp(ext, "tga") == 0)
    return IMAGE_TYPE_TGA;

  return IMAGE_TYPE_UNKNOWN;
}

// this is to be caerfal about type and reiten to be alowded for each and other
// type of image. such as PNG, JPG, tga, BPM. so if you would like to try to add
// new stuff image stuff use this lay out in the switch to make it a texture
// then add a opson in the header enum in the same enum layout
void Cmod_Window_draw_image(Cmod_Window *window, Posison_data pos,
                            Cmod_Window_Rect rect, ImageType image_type,
                            Path_t file) {
  SDL_Rect deck = {pos.x, pos.y, rect.w, rect.h};

  if (!window) {
    fprintf(stderr, "%s, you cant draw to somthing that dosent exist\n",
            __FUNCTION__);
    return;
  }
  if (file == NULL) {
    fprintf(stderr,
            "%s, how are you going to draw a image if you dont even have the "
            "file path.\n",
            __FUNCTION__);
    return;
  }
  if (image_type == IMAGE_TYPE_UNKNOWN) {
    printf("un desloded image type we will take care of it for you\n");
    image_type = detect_image_type(file);
    if (image_type == IMAGE_TYPE_UNKNOWN) {
      fprintf(stderr, "%s unable to find the image type. for %s", __FUNCTION__,
              file);
      return;
    } else {
      printf("we found the image type.");
    }
  }
  SDL_Surface *img_surfis;
  switch (image_type) {
  case IMAGE_TYPE_PNG:
    img_surfis = IMG_Load(file);
    break;
  case IMAGE_TYPE_JPG:
    img_surfis = IMG_Load(file);
    break;
  case IMAGE_TYPE_TGA:
    img_surfis = IMG_Load(file);
    break;
  case IMAGE_TYPE_BMP:
    img_surfis = IMG_Load(file);
    break;
  default:
    img_surfis = IMG_Load(file);
    break;
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(window->render, img_surfis);
    SDL_RenderCopy(window->render, texture, NULL, &deck);
    SDL_FreeSurface(img_surfis);
    SDL_DestroyTexture(texture);
  }
}
// dybamic pointers
void Store_dynamic_pointer(char *name, Pointer_t pointer) {
  if (!pointer_table) {
    printf("pleas run  DynamicPointer_setup(); before using the dybamic "
           "pointer as it will not work with out setup");
    return;
  }
  hash_table_insert(pointer_table, name, pointer);
}
Pointer_t Get_dynamic_pointer(char *name) {
  if (!pointer_table) {
    printf("pleas run  DynamicPointer_setup(); before using the dybamic "
           "pointer as it will not work with out setup");
    return NULL;
  }
  return hash_table_get(pointer_table, name);
}
MUST_BE_FREE Pointer_t Remove_dynamic_pointer(char *name) {
  if (!pointer_table) {
    printf("pleas run  DynamicPointer_setup(); before using the dybamic "
           "pointer as it will not work with out setup");
    return NULL;
  }
  Pointer_t timp = hash_table_get(pointer_table, name);
  hash_table_remove(pointer_table, name);
  return timp;
}

void DynamicPointer_Close() {
  if (pointer_table->count IS_NOT 0) {
    printf("you cant close the dynamic pointer table as you still have "
           "pointers alive plese kill them\n");
    return;
  }
  hash_table_destroy(pointer_table);
}
void DynamicPointer_setup() {
  if (pointer_table) {
    printf("the dinamic pointer is alraty setup.");
  }
  pointer_table = hash_table_create(2);
}
