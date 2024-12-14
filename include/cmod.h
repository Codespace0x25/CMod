#pragma once

// ============================= INCLUDES ===========================
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

// ============================ TYPES =============================

// the deconstructer for a object
typedef void Deleter;

// a general pointer 
typedef void* Pointer_t;

// A situation or surrounding substance within which something else originates, develops, or is contained. 
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
typedef enum {
    GET,
    POST,
    PUT,
    DELETE
} RequestType;


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
#define SHIFT_LEFT <<
#define SHIFT_RIGHT >>

// ============================= MACROS ===========================

#define cast(type) ((type))


// ============================ stdlib =============================

extern Pointer_t malloc(unsigned long size);


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

// ========================== HTTP API ===========================


String *http_request(RequestType type, String *url, String *headers, String *body);

// ========================== CUSTOM PRINTF =======================

void pprintf(const char *format, ...);
