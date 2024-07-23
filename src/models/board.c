#include <stdlib.h>
#include <stdio.h>

#include "board.h"

// ####################
// BOARD
// ####################

// POSITION

Position* position_new(int row, int column) {
  Position* position = malloc(sizeof(Position));

  if (position == NULL) {
    return NULL;
  }

  position->row = row;
  position->column = column;

  return position;
}

char* position_to_string(Position* position) {
  char* str = malloc(10 * sizeof(char));

  if (str == NULL) {
    return NULL;
  }

  sprintf(
    str,
    "(%d, %d)",
    position->row,
    position->column
  );

  return str;
}


// SQUARE

Square* square_new(Position* position, char mark) {
  Square* square = malloc(sizeof(Square));

  if (square == NULL) {
    return NULL;
  }

  square->position = position;
  square->mark = mark;

  return square;
}

char* square_to_string(Square* square) {
  char* str = malloc(20 * sizeof(char));

  if (str == NULL) {
    return NULL;
  }

  sprintf(
    str,
    "(%d, %d, %c)",
    square->position->row,
    square->position->column,
    square->mark
  );

  return str;
}


// BOARD

Board* board_new() {
  Board* board = malloc(sizeof(Board));

  if (board == NULL) {
    return NULL;
  }

  board->marks = 0;
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      board->squares[r][c] = square_new(position_new(r, c), BLANK);
    }
  }

  return board;
}

// char* board_to_string(Board* board) {
//   char* str = malloc(100 * sizeof(char));
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
