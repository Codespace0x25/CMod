#include "cmod.h"
#include <string.h>
#include <curl/curl.h>

// ========================== MATRIX API ==========================
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

void matrix_destroy(Matrix *m) {
    if (m) {
        for (size_t i = 0; i < m->rows; i++) {
            free(m->data[i]);
        }
        free(m->data);
        free(m);
    }
}

Matrix *matrix_add(const Matrix *a, const Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;

    Matrix *result = matrix_create(a->rows, a->cols);
    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return result;
}

Matrix *matrix_sub(const Matrix *a, const Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;

    Matrix *result = matrix_create(a->rows, a->cols);
    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }
    return result;
}

// ========================== STRING API ==========================
String *string_create(const char *initial_data) {
    size_t len = strlen(initial_data);
    String *s = (String *)malloc(sizeof(String));
    s->data = (char *)malloc((len + 1) * sizeof(char));
    strcpy(s->data, initial_data);
    s->length = len;
    return s;
}

void string_destroy(String *s) {
    if (s) {
        free(s->data);
        free(s);
    }
}

void string_replace(String *s, const char *find, const char *replace) {
    char *pos = strstr(s->data, find);
    if (!pos) return;

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

// ========================== HTTP API ===========================
static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    String *response = (String *)userdata;

    response->data = (char *)realloc(response->data, response->length + total_size + 1);
    memcpy(response->data + response->length, ptr, total_size);
    response->length += total_size;
    response->data[response->length] = '\0';

    return total_size;
}

String *http_request(RequestType type, String *url, String *headers, String *body) {
    CURL *curl = curl_easy_init();
    if (!curl) return NULL;

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

// ========================== CUSTOM PRINTF =======================
void pprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    const char *ptr = format;
    while (*ptr) {
        if (*ptr == '%' && *(ptr + 1) == 's') {
            String *s = va_arg(args, String *);
            printf("%s", s->data);
            ptr++;
        } else {
            putchar(*ptr);
        }
        ptr++;
    }

    va_end(args);
}
