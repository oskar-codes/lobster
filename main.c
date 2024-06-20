#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "context.h"
#include "tokenizer.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {

    context* ctx = create_context(10);
    value* v = create_value(STRING, "Hello, World!", 14);
    set_variable(ctx, "message", v);


    while (1) {
      char input[256];
      printf(">>> ");
      fgets(input, 256, stdin);
      // remove newline
      input[strcspn(input, "\n")] = 0;
      if (strcmp(input, "exit") == 0) {
        break;
      }
      printf("Started tokenizing '%s'\n", input);
      Token* tokens;
      int length = strlen(input);
      int count = tokenize(input, length, &tokens);
      printf("Tokenized %d tokens\n", count);
      for (int i = 0; i < count; i++) {
        Token t = tokens[i];
        print_token(t);
      }

      free_tokens(tokens);
    }



    free_context(ctx);

  }

  return 0;
}