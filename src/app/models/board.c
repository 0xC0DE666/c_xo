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
Matrix* board_new(unsigned rows, unsigned columns) {
  Matrix* board = matrix_new(rows, columns);

  for (unsigned r = 0; r < board->rows; r++) {
    for (unsigned c = 0; c < board->columns; c++) {
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
bool win_line(Array* line, unsigned n_to_win) {
  for (unsigned i = 0; i < line->size - 1; ++i) {
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

bool win(Matrix* board, unsigned n_to_win) {
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
        // printf("win col %d\n", r);
        win = true;
        break;
    }
    array_clear(row, NULL);
    array_clear(col, NULL);
  }

  if (win) {
    array_free(&row, NULL);
    array_free(&col, NULL);
    return true;
  }
  printf("\n\n");

  // check diags
  // let mut left_row = 0;
  // let mut left_col = 0;

  // let mut right_row = 0;
  // let mut right_col = 2;

  // let mut left_line: Vec<char> = vec![];
  // let mut right_line: Vec<char> = vec![];

  // for _i in 0..n {
  //     let left_mark = board.get_mark(&Position {
  //         row: left_row,
  //         col: left_col,
  //     });
  //     let right_mark = board.get_mark(&Position {
  //         row: right_row,
  //         col: right_col,
  //     });

  //     left_line.push(left_mark);
  //     right_line.push(right_mark);

  //     left_row += 1;
  //     left_col += 1;

  //     right_row += 1;
  //     if right_col > 0 {
  //         right_col -= 1;
  //     }
  // }
  // if check_line(&left_line) {
  //     println!("win diag left down");
  //     return true;
  // } else if check_line(&right_line) {
  //     println!("win diag right down");
  //     return true;
  // }
  return false;
}
