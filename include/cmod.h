#pragma once

// ============================= INCLUDES ===========================
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// ============================ TYPES =============================

// the deconstructer for a object
typedef void Deleter;

// a general pointer
typedef void *Pointer_t;

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

// =========================== DEFINITION ==========================

#define L_AND &&
#define L_OR ||
#define AND &
#define OR |
#define LESS_THAN <
#define GREATER_THAN >
#define LESS_THAN_OR_EQUAL <=
#define GREATER_THAN_OR_EQUAL >=
#define IS ==
#define IS_NOT !=
#define MODULO %
#define INC ++
#define DEC --
#define INC_BY +=
#define DEC_BY -=
#define SHIFT_LEFT <<
#define SHIFT_RIGHT >>
#define MUST_BE_FREE [[nodiscard]]

// ========================== MATRIX API ==========================

Matrix *matrix_create(size_t rows, size_t cols);

Deleter matrix_destroy(Matrix *m);

Matrix *matrix_add(const Matrix *a, const Matrix *b);

Matrix *matrix_sub(const Matrix *a, const Matrix *b);

Matrix *matrix_mul(const Matrix *a, const Matrix *b);

Matrix *matrix_div(const Matrix *a, const Matrix *b);

// ========================== STRING API ==========================

String *string_create(const char *initial_data);

Deleter string_destroy(String *s);

void string_replace(String *s, const char *find, const char *replace);

String *string_find(const String *s, const char *substring);

void pprintf(const char *format, ...);

// ============================= MACROS ===========================

#define Make_String(name, data) (String *name = string_create(data))
#define To_char(input) (input->data)

// ========================== FILE API ===========================

void write_file(String filepath, String *input);

String *read_file(String filepast);

// ========================== HTTP API ===========================

String *http_request(RequestType type, String *url, String *headers,
                     String *body);

// ========================== LIST API =======================
MUST_BE_FREE Queue_t *queue_create();
void queue_destroyer(Queue_t *queue);
void queue_add(Queue_t *queue, char *data);
char *queue_pull(Queue_t *queue);
