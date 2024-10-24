#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#include "./utils.h"

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

bool ask_play_again() {
  char input[10] = {0};
  char yes[] = "yes\n";
  char no[] = "no\n";

  while (true) {
    printf("Wanna play again? [yes/no]\n");
    fgets(input, 10, stdin);

    bool y = strcmp(input, yes) == 0;
    bool n = strcmp(input, no) == 0;

    if (y || n) {
      return strcmp(input, yes) == 0 ? true : false;
    }
    printf("Please enter yes or no.\n");
  }
}
