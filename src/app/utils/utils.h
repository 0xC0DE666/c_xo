#include <stdbool.h>

#ifndef UTILS_H
#define UTILS_H

// ********************
// IO
// ********************

char* string_new(int length);
void string_free(char** string);
int string_length(char buffer[]);

int read_line(char buffer[], int capacity);
int read_int();

int get_index_to_mark(int min, int max);
bool ask_play_again();

// ********************
// MISC
// ********************
  void ptr_free(void** ptr);

  char* bool_to_str(bool* b);

#endif
