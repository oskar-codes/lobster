#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OP_ADD "+"
#define OP_SUB "-"
#define OP_MUL "*"
#define OP_DIV "/"
#define OP_MOD "%"
#define OP_POW "^"
#define OP_ASSIGN "="
#define OP_EQ "=="
#define OP_NE "!="
#define OP_GT ">"
#define OP_LT "<"
#define OP_GE ">="
#define OP_LE "<="
#define OP_AND "&&"
#define OP_OR "||"
#define OP_NOT "!"
#define OP_TEST "~~"

#define N_OP 17

#define OPERATORS { OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_POW, OP_ASSIGN, OP_EQ, OP_NE, OP_GT, OP_LT, OP_GE, OP_LE, OP_AND, OP_OR, OP_NOT, OP_TEST }

int is_operator_start(char input);

enum TokenType {
  TOKEN_TYPE_NUMBER,
  TOKEN_TYPE_STRING,
  TOKEN_TYPE_IDENTIFIER,
  TOKEN_TYPE_OPERATOR,
  TOKEN_TYPE_LPAREN,
  TOKEN_TYPE_RPAREN,
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

