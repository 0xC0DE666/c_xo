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


// BOARD
Matrix* board_new(int rows, int columns) {
  Matrix* board = matrix_new(rows, columns);

  for (int r = 0; r < board->rows; r++) {
    for (int c = 0; c < board->columns; c++) {
      Position pos = position_new(r, c);
      Square* sqr = square_new(pos, BLANK);
      matrix_insert(board, &pos, sqr);
    }
  }

  return board;
}

void board_free(Matrix** board) {
  matrix_free(board, (FreeFn) square_free);
}


// WIN
bool win_line(Array* line, int n_to_win) {
  for (int i = 0; i < line->size - 1; ++i) {
    Square* a = (Square*) array_get(line, i);
    Square* b = (Square*) array_get(line, i + 1);

    bool blank_sqr = a->mark == BLANK || b->mark == BLANK;
    bool marks_differ = a->mark != b->mark;

    if (blank_sqr || marks_differ) {
        return false;
    }
  }

  return true;
}

bool win_straight(Matrix* board, int n_to_win) {
  // check straight lines
  Array* row = array_new(board->rows);
  Array* col = array_new(board->columns);
  bool win = false;

  for (int r = 0; r < board->rows; ++r) {
    for (int c = 0; c < board->columns; ++c) {
      Position pos = position_new(r, c);
      Square* sqr = (Square*) matrix_get(board, &pos);
      array_append(row, sqr);

      pos = position_new(c, r);
      sqr = (Square*) matrix_get(board, &pos);
      array_append(col, sqr);
    }
    // printf("win? %s\n", array_to_string(row, (ToStringFn) square_to_string));
    // printf("hello --> \n");
    if (win_line(row, n_to_win)) {
      // printf("win row %d\n", r);
      win = true;
      break;
    }
    if (win_line(col, n_to_win)) {
      // printf("win col %d\n", c);
      win = true;
      break;
    }
    array_clear(row, NULL);
    array_clear(col, NULL);
  }

  array_free(&row, NULL);
  array_free(&col, NULL);

  return win;
}

bool win_diagonal(Matrix* board, int n_to_win) {
  // check diagonal lines
  int left_row = 0;
  int left_col = 0;

  int right_row = 0;
  int right_col = board->columns - 1;

  Array* left_line = array_new(board->rows);
  Array* right_line = array_new(board->rows);

  for (int i = 0; i < board->rows; ++i) {
      Position left_pos = position_new(left_row, left_col);
      Square* left_sqr = matrix_get(board, &left_pos);

      Position right_pos = position_new(right_row, right_col);
      Square* right_sqr = matrix_get(board, &right_pos);

      array_append(left_line, left_sqr);
      array_append(right_line, right_sqr);

      left_row += 1;
      left_col += 1;

      right_row += 1;
      if (right_col > 0) {
          right_col -= 1;
      }
  }

  bool win = false;
  if (win_line(left_line, n_to_win)) {
      // printf("win diag left down\n");
      win = true;
  }
  if (win_line(right_line, n_to_win)) {
      // printf("win diag right down\n");
      win = true;
  }

  array_free(&left_line, NULL);
  array_free(&right_line, NULL);

  return win;
}

bool win(Matrix* board, int n_to_win) {
  if (board->size < n_to_win) {
    return false;
  }
  if (win_straight(board, n_to_win)) {
    return true;
  }
  return win_diagonal(board, n_to_win);
}
