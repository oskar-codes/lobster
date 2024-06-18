#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tokenizer.h"

int is_operator(char input) {
  return (input == OP_ADD) ||
         (input == OP_SUB) ||
         (input == OP_MUL) ||
         (input == OP_DIV) ||
         (input == OP_MOD) ||
         (input == OP_POW) ||
         (input == OP_ASSIGN);
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
    } else if (is_operator(current)) {
      char* value = malloc(2);
      value[0] = current;
      value[1] = '\0';
      Token t = create_token(TOKEN_TYPE_OPERATOR, value);
      resize();
      (*tokens)[token_count++] = t;
      advance();
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





