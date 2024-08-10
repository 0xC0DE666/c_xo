#include <stdlib.h>
#include <stdio.h>

char* string_new(int length) {
  char* string = malloc(length * sizeof(char));

  if (string == NULL) {
    return NULL;
  }

  // string = "";

  return string;
}

void string_free(char** string) {
  free(*string);
  *string = NULL;
}

int string_length(char* string) {
  int i = 0;
  while (string[i]) {
    ++i;
  }
  return i;
}

int read_line(char buffer[], int size) {
  int i, c;
  for (i = 0; i < size - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
    buffer[i] = c;
  }
  buffer[i] = '\0';
  return i;
}
