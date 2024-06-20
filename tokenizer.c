#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tokenizer.h"

int is_operator_start(char input) {
  char* operators[] = OPERATORS;
  for (int i = 0; i < N_OP; i++) {
    if (input == operators[i][0]) {
      return 1;
    }
  }
  return 0;
}

int is_alpha(char input) {
  return (input >= 'a' && input <= 'z') ||
         (input >= 'A' && input <= 'Z');
}
int is_digit(char input) {
  return input >= '0' && input <= '9';
}
int is_alnum(char input) {
  return is_alpha(input) || is_digit(input);
}
int nostrend(char input) {
  return input != '"';
}

void print_token(Token t) {
  if (t.type == TOKEN_TYPE_NUMBER) {
    printf("<Number(%s)>\n", t.value);
  } else if (t.type == TOKEN_TYPE_STRING) {
    printf("<String(%s)>\n", t.value);
  } else if (t.type == TOKEN_TYPE_IDENTIFIER) {
    printf("<Identifier(%s)>\n", t.value);
  } else if (t.type == TOKEN_TYPE_OPERATOR) {
    printf("<Operator(%s)>\n", t.value);
  } else if (t.type == TOKEN_TYPE_EOF) {
    printf("<EOF>\n");
  }
}

Token create_token(int type, char* value) {
  Token t = {
    .type = type,
    .value = value
  };
  return t;
}

typedef int (*condition)(char);

Token parse_while(char* input, int* size, condition cond, int type) {
  char* start = input;
  while (cond(*input)) {
    input++;
    (*size)++;
  }
  int length = input - start;
  char* value = malloc(length + 1);
  memcpy(value, start, length);
  value[length] = '\0';
  return create_token(type, value);
}

void free_tokens(Token* tokens) {
  for (int i = 0; tokens[i].type != TOKEN_TYPE_EOF; i++) {
    free(tokens[i].value);
  }
  free(tokens);
}

int tokenize(char* input, int size, Token** tokens) {

#define advance() input++; i++;
#define current input[0]
#define resize() *tokens = realloc(*tokens, sizeof(Token) * (token_count + 1))

  if (input == NULL) {
    return 0;
  }
  *tokens = calloc(1, sizeof(Token));
  int token_count = 0;

  int i = 0;
  while (i < size) {
    if (current == ' ') {
      advance();
      continue;
    } else if (current >= '0' && current <= '9') {
      int size = 0;
      Token result = parse_while(input, &size, is_digit, TOKEN_TYPE_NUMBER);
      i += size;
      input += size;
      resize();
      (*tokens)[token_count++] = result;
    } else if (current == '"') {
      int size = 0;
      advance(); // skip the leading "
      Token result = parse_while(input, &size, nostrend, TOKEN_TYPE_STRING);
      i += size;
      input += size;
      advance(); // skip the trailing "
      resize();
      (*tokens)[token_count++] = result;
    } else if (is_alpha(current)) {
      int size = 0;
      Token result = parse_while(input, &size, is_alpha, TOKEN_TYPE_IDENTIFIER);
      i += size;
      input += size;
      resize();
      (*tokens)[token_count++] = result;
    } else if (is_operator_start(current)) {
      char* operators[] = OPERATORS;
      int max_length = 0;
      char* max_operator = NULL;
      for (int j = 0; j < N_OP; j++) {
        int length = strlen(operators[j]);
        if (strncmp(input, operators[j], length) == 0 && length > max_length) {
          max_length = length;
          if (max_operator != NULL) {
            free(max_operator); // Free the previously allocated memory
          }
          max_operator = malloc(length + 1);
          strcpy(max_operator, operators[j]);
        }
      }
      if (max_length == 0) {
        fprintf(stderr, "Unexpected character: '%c'\n", current);
        free(max_operator); // Free the allocated memory
        exit(1);
      }
      Token result = create_token(TOKEN_TYPE_OPERATOR, max_operator);
      i += max_length;
      input += max_length;
      resize();
      (*tokens)[token_count++] = result;

    } else {
      fprintf(stderr, "Unexpected character: '%c'\n", current);
      exit(1);
    }
  }

  Token eof = create_token(TOKEN_TYPE_EOF, NULL);
  resize();
  (*tokens)[token_count++] = eof;

  return token_count;
}





