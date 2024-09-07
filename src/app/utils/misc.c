#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void ptr_free(void** ptr) {
  free(*ptr);
  *ptr = NULL;
}

char* bool_to_str(bool* b) {
  char* str_b = malloc(6);

  sprintf(
    str_b,
    "%s",
    *b ? "true" : "false"
  );

  return str_b;
}
