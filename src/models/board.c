#include <stdlib.h>
#include <stdio.h>

#include "board.h"

Board *board_new() {
  Board *board = malloc(sizeof(Board));

  if (board == NULL) {
    return NULL;
  }

  board->marks = 0;
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      board->values[r][c] = ' ';
    }
  }

  return board;
}

// char *board_to_string(Board *board) {
//   char *str = malloc(100 * sizeof(char));
// 
//   sprintf(
//     str,
//     "%s (%c) %d",
//     board->name,
//     board->symbol,
//     board->score
//   ); 
// 
//   return str;
// }
