#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "./misc.h"

char* string_new(int length) {
  char* string = malloc(length * sizeof(char));

  if (string == NULL) {
    return NULL;
  }

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

int read_line(char buffer[], int capacity) {
  int i, c;
  for (i = 0; i < capacity - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
    buffer[i] = c;
  }
  buffer[i] = '\0';
  return i;
}

int get_index_to_mark(int min, int max) {
  char input[10] = {0};
  int idx = -1;

  while (idx < min || idx > max) {
    idx = atoi(fgets(input, 10, stdin));

    if (idx < min || idx > max) {
      printf("Position out of range, please enter a number between %d and %d.\n", min, max);
    }
  }

  return idx;
}
