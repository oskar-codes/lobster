
#define ERR_NONE 0

enum error_codes {
  ERR_TOKENIZER = -128,
  ERR_AST,
  ERR_INTERPRETER
};

typedef struct {
  int code;
  char *message;
} error;
