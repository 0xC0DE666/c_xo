#include <stdlib.h>
#include <stdio.h>

#include "../utils/io.h"
#include "board.h"

// SQUARE

Square* square_new(Position position, char mark) {
  Square* square = malloc(sizeof(Square));

  if (square == NULL) {
    return NULL;
  }

  square->position = position;
  square->mark = mark;

  return square;
}

void square_free(Square** square) {
  free(*square);
  *square = NULL;
}

char* square_to_string(Square* square) {
  char* str = string_new(20);

  if (str == NULL) {
    return NULL;
  }

  sprintf(
    str,
    "(%d, %d, %c)",
    square->position.row,
    square->position.column,
    square->mark
  );

  return str;
}

