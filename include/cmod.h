#ifndef CMOD_H
#define CMOD_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
// ========================== DEFINUSHON ==========================
#define AND &&
#define OR ||
#define LESS_THEN <
#define GRADER_THEN >
#define LESS_THEN_OR_EQULE <=
#define GRADER_THEN_OR_EQULE >=
#define IS ==
#define IS_NOT !=

// ========================== MATRIX API ==========================
typedef struct Matrix {
    float **data;
    size_t rows;
    size_t cols;
} Matrix;

// Matrix operations
Matrix *matrix_create(size_t rows, size_t cols);
void matrix_destroy(Matrix *m);
Matrix *matrix_add(const Matrix *a, const Matrix *b);
Matrix *matrix_sub(const Matrix *a, const Matrix *b);
Matrix *matrix_mul(const Matrix *a, const Matrix *b);
Matrix *matrix_div(const Matrix *a, const Matrix *b);

// ========================== STRING API ==========================
typedef struct String {
    char *data;
    size_t length;
} String;

// String operations
String *string_create(const char *initial_data);
void string_destroy(String *s);
void string_replace(String *s, const char *find, const char *replace);
String *string_find(const String *s, const char *substring);

// ========================== HTTP API ===========================
typedef enum {
    GET,
    POST,
    PUT,
    DELETE
} RequestType;

String *http_request(RequestType type, String *url, String *headers, String *body);

// ========================== CUSTOM PRINTF =======================
void pprintf(const char *format, ...);

#endif // PROME_C_H
