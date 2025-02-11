#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#define ENABLE_FILE
#include <cmod.h>

typedef enum {
  SEMI,
  OPEN_PAREN,
  CLOSE_PAREN,
} Token_SEPARATOR;

typedef enum {
  EXIT,
} Token_KEYWORDS;

typedef enum {
  INT,
} Token_Literal;

typedef struct {
  Token_KEYWORDS type;
} Token_Keywaed_t;

typedef struct {
  Token_SEPARATOR type;
} Token_Separator_t;

typedef struct {
  Token_Literal type;
  int value;
} Token_Literal_t;

void lexer(FILE *file) {
  char current = fgetc(file);
  while (current != EOF) {
    if (current == ';') {
      printf("foudn ;\n");
    } else if (current == '(') {
      printf("foudn (\n");
    } else if (current == ')') {
      printf("foudn )\n");
    } else if (isdigit(current)) {
      printf("found number %d\n", current - '0');
    } else if (isalpha(current)) {
      printf("found charter %c\n", current);
    }
    current = fgetc(file);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  String *timp = string_create(argv[1]);
  FILE *file;
  file = fopen(To_char(timp), "r");
  lexer(file);
  return 0;
}
