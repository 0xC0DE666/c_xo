#include <stdlib.h>
#include <stdio.h>

#include "../utils/utils.h"
#include "models.h"

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

bool square_is_blank(Grid* board, Position* position) {
  if (grid_position_valid(board, position) == false) {
    return false;
  }
  
  Square* sqr = grid_get(board, position).ok;
  return sqr->mark == UNMARKED;
}

void square_clear(Square* square) {
  square->mark = UNMARKED;
}


// BOARD
Grid* board_new(int rows, int columns) {
  Grid* board = grid_new(rows, columns).ok;

  for (int r = 0; r < board->rows; r++) {
    for (int c = 0; c < board->columns; c++) {
      Position pos = position_new(r, c);
      Square* sqr = square_new(pos, UNMARKED);
      grid_set(board, &pos, sqr);
    }
  }

  return board;
}

void board_free(Grid** board) {
  grid_free(board, (FreeFn) square_free);
}

void board_clear(Grid* board) {
  grid_for_each(board, (GridEachFn) square_clear);
}

void board_print(Grid* board) {
  int i = 0;
  for (int r = 0; r < board->rows; ++r) {
    printf("\t   ");
    for (int c = 0; c < board->columns; ++c) {
      ++i;
      Position pos = position_new(r, c);
      Square* sqr = grid_get(board, &pos).ok;

      if (sqr->mark == UNMARKED) {
        printf(" %d ", i);
      } else {
        printf(" %c ", sqr->mark);
      }

      if (c < board->columns - 1) {
        printf("|");
      }

      if (c == board->columns - 1) {
        printf("\n");
      }
    }
    if (r == board->rows - 1) {
      continue;
    }

    printf("\t   ");
    for (int l = 0; l < board->rows * 4 - 1; ++l) {
      printf("-");
      if (l == board->columns * 4 - 2) {
        printf("\n");
      }
    }
  }
}

int board_mark(Grid* board, Position* position, char mark) {
  if (grid_position_valid(board, position) == false) {
    return 1;
  }
  
  Square* sqr = (Square*) grid_get(board, position).ok;
  if (sqr->mark != UNMARKED) {
    return 1;
  }

  sqr->mark = mark;
  return 0;
}

Position index_to_position(Grid* board, int index) {
  for (int r = 0; r < board->rows; ++r) {
    for (int c = 0; c < board->columns; ++c) {
      --index;
      if (index == 0) {
        return position_new(r, c);
      }
    }
  }
}


// WIN
bool win_line(Array* line, int n_to_win) {
  for (int a = 0; a < line->capacity; ++a) {
    for (int i = a; i < n_to_win - 1; ++i) {
      Square* a = (Square*) array_get(line, i).ok;
      Square* b = (Square*) array_get(line, i + 1).ok;

      bool blank_sqr = a->mark == UNMARKED || b->mark == UNMARKED;
      bool marks_differ = a->mark != b->mark;

      if (blank_sqr || marks_differ) {
          return false;
      }
    }
  }

  return true;
}

bool win_straight(Grid* board, int n_to_win) {
  // check straight lines
  Array* row = array_new(board->rows).ok;
  Array* col = array_new(board->columns).ok;
  bool win = false;

  for (int r = 0; r < board->rows; ++r) {
    for (int c = 0; c < board->columns; ++c) {
      Position pos = position_new(r, c);
      Square* sqr = grid_get(board, &pos).ok;
      array_append(row, sqr);

      pos = position_new(c, r);
      sqr = grid_get(board, &pos).ok;
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

bool win_diagonal(Grid* board, int n_to_win) {
  // check diagonal lines
  int left_row = 0;
  int left_col = 0;

  int right_row = 0;
  int right_col = board->columns - 1;

  Array* left_line = array_new(board->rows).ok;
  Array* right_line = array_new(board->rows).ok;

  for (int i = 0; i < board->rows; ++i) {
      Position left_pos = position_new(left_row, left_col);
      Square* left_sqr = grid_get(board, &left_pos).ok;

      Position right_pos = position_new(right_row, right_col);
      Square* right_sqr = grid_get(board, &right_pos).ok;

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

bool win(Grid* board, int n_to_win) {
  if (board->size < n_to_win) {
    return false;
  }
  if (win_straight(board, n_to_win)) {
    return true;
  }
  return win_diagonal(board, n_to_win);
}
