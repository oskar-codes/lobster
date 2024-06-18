#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "context.h"
#include "error.h"


value* create_value(int type, void* data, int size) {
  if (data == NULL) {
    return NULL;
  }
  value* v = calloc(1, sizeof(value));
  v->type = type;
  v->data = malloc(size);
  v->size = size;
  memcpy(v->data, data, size);
  return v;
}

variable* create_variable(char* name, value* value) {
  if (name == NULL || value == NULL) {
    return NULL;
  }
  variable* v = calloc(1, sizeof(variable));
  v->name = name;
  v->value = value;
  return v;
}

context* create_context(int size) {
  if (size <= 0) {
    return NULL;
  }
  context* ctx = calloc(1, sizeof(context));
  ctx->size = size;
  ctx->variables = calloc(size, sizeof(variable));
  return ctx;
}

variable* get_variable(context* ctx, char* name) {
  if (ctx == NULL || name == NULL) {
    return NULL;
  }
  for (int i = 0; i < ctx->size; i++) {
    if (strcmp(ctx->variables[i].name, name) == 0) {
      return &ctx->variables[i];
    }
  }
  return NULL;
}

void set_variable(context* ctx, char* name, value* value) {
  if (ctx == NULL || name == NULL || value == NULL) {
    return;
  }
  for (int i = 0; i < ctx->size; i++) {
    if (ctx->variables[i].name == NULL) {
      continue;
    }
    if (strcmp(ctx->variables[i].name, name) == 0) {
      ctx->variables[i].value = value;
      return;
    }
  }
  for (int i = 0; i < ctx->size; i++) {
    if (ctx->variables[i].name == NULL) {
      ctx->variables[i].name = name;
      ctx->variables[i].value = value;
      return;
    }
  }
}

void free_context(context* ctx) {
  if (ctx == NULL) {
    return;
  }
  for (int i = 0; i < ctx->size; i++) {
    if (ctx->variables[i].name != NULL) {
      free(ctx->variables[i].value->data);
      free(ctx->variables[i].value);
    }
  }
  free(ctx->variables);
  free(ctx);
}

