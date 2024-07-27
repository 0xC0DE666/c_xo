#include <stdlib.h>
#include <stdio.h>

#include "../utils/io.h"
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

void position_free(Position** position) {
  free(*position);
  *position = NULL;
}

char* position_to_string(Position* position) {
  char* str = string_new(10);

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

void square_free(Square** square) {
  position_free(&(*square)->position);
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

void board_free(Board** board) {
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      Position** p = &((*board)->squares[r][c]->position);
      position_free(p);
      Square** s = &((*board)->squares[r][c]);
      square_free(s);
    }
  }
  free(*board);
  (*board) = NULL;
}

// char* board_to_string(Board* board) {
//   char* str = string_new(100);
// 
//   for (int r = 0; r < 3; ++r) {
//     for (int c = 0; c < 3; ++c) {
//       board->squares[r][c] = square_new(position_new(r, c), BLANK);
//     }
//   }
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

void board_mark(Board* board, Position* position, char mark) {
  int row = position->row;
  int col = position->column;
  board->squares[row][col]->mark = mark;
}

char board_get_mark(Board* board, Position* position) {
  int row = position->row;
  int col = position->column;
  return board->squares[row][col]->mark;
}
