#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OP_ADD '+'
#define OP_SUB '-'
#define OP_MUL '*'
#define OP_DIV '/'
#define OP_MOD '%'
#define OP_POW '^'
#define OP_ASSIGN '='

int is_operator(char input);

enum TokenType {
  TOKEN_TYPE_NUMBER,
  TOKEN_TYPE_STRING,
  TOKEN_TYPE_IDENTIFIER,
  TOKEN_TYPE_OPERATOR,
  TOKEN_TYPE_EOF
};

typedef struct Token {
  int type;
  char* value;
} Token;

Token create_token(int type, char* value);

void print_token(Token t);

Token parse_while(char* input, int* size, int (*cond)(char), int type);

void free_tokens(Token* tokens);

int tokenize(char* input, int length, Token** tokens);

