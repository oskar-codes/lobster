
enum Type {
  NUMBER,
  STRING,
  BOOLEAN,
  OBJECT,
  ARRAY,
  FUNCTION,
  NONE,
};

typedef struct {
  int type;
  int size;
  void* data;
} value;

typedef struct {
  char* name;
  value* value;
} variable;

typedef struct {
  int size;
  variable* variables;
} context;

/**
 * Create a value
 * @param type
 * @param value
 * @param size
 * @return value*
 */
value* create_value(int type, void* data, int size);

/**
 * Create a variable
 * @param name
 * @param value
 */
variable* create_variable(char* name, value* value);

/**
 * Create a context
 * @param size
 */
context* create_context(int size);

/**
 * Get a variable from a context
 * @param ctx
 * @param name
 */
variable* get_variable(context* ctx, char* name);

/**
 * Set a variable in a context
 * @param ctx
 * @param name
 * @param value
 */
void set_variable(context* ctx, char* name, value* value);


void free_context(context* ctx);

