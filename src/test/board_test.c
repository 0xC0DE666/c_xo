#include <stdbool.h>
#include <string.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../app/utils/io.h"
#include "../app/models/board.h"

// ####################
// square_new
// ####################
Test(square_new, _1) {
  Square* square = square_new(position_new(0, 1), 'O');

  cr_assert_eq(square != NULL, true);
  cr_assert_eq(square->position.row, 0);
  cr_assert_eq(square->position.column, 1);
  cr_assert_eq(square->mark, 'O');

  square_free(&square);
}

// ####################
// square_free
// ####################
Test(square_free, _1) {
  Square* square = square_new(position_new(1, 2), BLANK);

  cr_assert_eq(square == NULL, false);

  square_free(&square);

  cr_assert_eq(square, NULL);
}

// ####################
// square_to_string
// ####################
Test(square_to_string, _1) {
  Square* square = square_new(position_new(1, 1), 'X');

  char* result= square_to_string(square);
  char* expected = "(1, 1, X)";

  cr_assert_eq(strcmp(result, expected), 0);

  square_free(&square);
  string_free(&result);
}

// ####################
// win_line
// ####################
Test(win_line, false_blank_sqr) {
  Array* line = array_new(3);

  for (unsigned i = 0; i < line->capacity; i++) {
    Square* sqr = square_new(position_new(0, i), i == 0 ? BLANK : 'X');
    array_append(line, sqr);
  }
  
  bool result = win_line(line, line->size);

  cr_assert_eq(result, false);

  array_free(&line, (FreeFn) square_free);
}

Test(win_line, false_marks_differ) {
  Array* line = array_new(3);

  for (unsigned i = 0; i < line->capacity; i++) {
    Square* sqr = square_new(position_new(0, i), i == 0 ? 'O' : 'X');
    array_append(line, sqr);
  }
  
  bool result = win_line(line, line->size);

  cr_assert_eq(result, false);

  array_free(&line, (FreeFn) square_free);
}

Test(win_line, true_win) {
  Array* line = array_new(3);

  for (unsigned i = 0; i < line->capacity; i++) {
    Square* sqr = square_new(position_new(0, i), 'X');
    array_append(line, sqr);
  }
  
  bool result = win_line(line, line->size);

  cr_assert_eq(result, true);

  array_free(&line, (FreeFn) square_free);
}

// ####################
// win
// ####################
Test(win_line, win_straight_lines) {
  Matrix* board = matrix_new(3, 3);

  for (unsigned r = 0; r < board->rows; r++) {
    for (unsigned c = 0; c < board->columns; c++) {
      Position pos = position_new(r, c);
      Square* sqr = square_new(pos, BLANK);
      matrix_insert(board, &pos, sqr);
    }
  }
  // char* str_board = matrix_to_string(board, (ToStringFn) square_to_string);
  
  unsigned n_to_win = 3;
  for (unsigned r = 0; r < board->rows; r++) {
    ///////////////
    // test rows
    ///////////////
    for (unsigned c = 0; c < board->columns; c++) {
      Position pos = position_new(r, c);
      Square* sqr = (Square*) matrix_get(board, &pos);
      sqr->mark = 'X';
    }

    // str_board = matrix_to_string(board, (ToStringFn) square_to_string);
    // printf("test r%d\n%s\n", r, str_board);

    bool result = win(board, n_to_win);
    cr_assert_eq(result, true);

    for (unsigned c = 0; c < board->columns; c++) {
      Position pos = position_new(r, c);
      Square* sqr = (Square*) matrix_get(board, &pos);
      sqr->mark = BLANK;
    }
    // printf("\n\n");

    ///////////////
    // test columns
    ///////////////
    for (unsigned c = 0; c < board->columns; c++) {
      Position pos = position_new(c, r);
      Square* sqr = (Square*) matrix_get(board, &pos);
      sqr->mark = 'X';
    }

    // str_board = matrix_to_string(board, (ToStringFn) square_to_string);
    // printf("test c%d\n%s\n", r, str_board);

    result = win(board, n_to_win);
    cr_assert_eq(result, true);

    for (unsigned c = 0; c < board->columns; c++) {
      Position pos = position_new(c, r);
      Square* sqr = (Square*) matrix_get(board, &pos);
      sqr->mark = BLANK;
    }
    // printf("\n\n");
  }

  matrix_free(&board, (FreeFn) square_free);
}
