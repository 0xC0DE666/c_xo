#include <stdbool.h>
#include <string.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../app/utils/io.h"
#include "../app/utils/misc.h"
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

  char* result = square_to_string(square);
  char* expected = "(1, 1, X)";

  cr_assert_eq(strcmp(result, expected), 0);

  square_free(&square);
  string_free(&result);
}

// ####################
// square_is_blank
// ####################
Test(square_is_blank, _1) {
  Matrix* board = board_new(3, 3);
  Position pos;

  for (int i = 0; i < board->columns; ++i) {
    pos = position_new(i, i);
    board_mark(board, &pos, 'X');
  }

  for (int r = 0; r < board->rows; ++r) {
    for (int c = 0; c < board->columns; ++c) {
      pos = position_new(r, c);

      if (r == c) {
        cr_assert_eq(square_is_blank(board, &pos), false);
      } else {
        cr_assert_eq(square_is_blank(board, &pos), true);
      }
    }
  }

  board_free(&board);
}


// ####################
// board_new
// ####################
Test(board_new, _1) {
  Matrix* board = board_new(3, 3);

  for (int r = 0; r < board->rows; r++) {
    for (int c = 0; c < board->columns; c++) {
      Position pos = position_new(r, c);
      Square* sqr = matrix_get(board, &pos).ok;
      cr_assert_eq(sqr != NULL, true);
      cr_assert_eq(sqr->position.row, r);
      cr_assert_eq(sqr->position.column, c);
      cr_assert_eq(sqr->mark, BLANK);
    }
  }

  board_free(&board);
}

// ####################
// board_free
// ####################
Test(board_free, _1) {
  Matrix* board = board_new(3, 3);

  cr_assert_eq(board == NULL, false);

  board_free(&board);

  cr_assert_eq(board, NULL);
}

// ####################
// board_clear
// ####################
void mark_x(Square* sqr) {
  sqr->mark = 'X'; 
}

bool marked(Square* sqr) {
  return sqr->mark != BLANK;
}

void test_marked(Square* sqr) {
  cr_assert_eq(marked(sqr), true);
}

void test_unmarked(Square* sqr) {
  cr_assert_eq(marked(sqr), false);
}

Test(board_clear, _1) {
  Matrix* board = board_new(3, 3);
  matrix_for_each(board, (MatrixEachFn) mark_x);
  matrix_for_each(board, (MatrixEachFn) test_marked);

  board_clear(board);

  matrix_for_each(board, (MatrixEachFn) test_unmarked);

  board_free(&board);
}

// ####################
// board_mark
// ####################
Test(board_mark, _1) {
  Matrix* board = board_new(3, 3);
  Position pos = position_new(-1, 1);

  //fail: position invalid
  int res = board_mark(board, &pos, 'X');
  cr_assert_eq(res, 1);

  // success
  pos.row = 1;
  res = board_mark(board, &pos, 'X');
  cr_assert_eq(res, 0);
  Square* sqr = matrix_get(board, &pos).ok;
  cr_assert_eq(sqr->mark, 'X');

  //fail: already marked
  res = board_mark(board, &pos, 'X');
  cr_assert_eq(res, 1);

  board_free(&board);
}

// ####################
// index_to_position
// ####################
Test(index_to_position, _1) {
  Matrix* board = board_new(3, 3);

  int i = 1;
  for (int r = 0; r < board->rows; ++r) {
    for (int c = 0; c < board->columns; ++c) {
      Position pos = index_to_position(board, i);
      cr_assert_eq(pos.row, r);
      cr_assert_eq(pos.column, c);
      ++i;
    }
  }

  board_free(&board);
}


// ####################
// win_line
// ####################
Test(win_line, false_blank_sqr) {
  Array* line = array_new(3).ok;

  for (int i = 0; i < line->capacity; i++) {
    Square* sqr = square_new(position_new(0, i), i == 0 ? BLANK : 'X');
    array_append(line, sqr);
  }
  
  bool result = win_line(line, line->size);

  cr_assert_eq(result, false);

  array_free(&line, (FreeFn) square_free);
}

Test(win_line, false_marks_differ) {
  Array* line = array_new(3).ok;

  for (int i = 0; i < line->capacity; i++) {
    Square* sqr = square_new(position_new(0, i), i == 0 ? 'O' : 'X');
    array_append(line, sqr);
  }
  
  bool result = win_line(line, line->size);

  cr_assert_eq(result, false);

  array_free(&line, (FreeFn) square_free);
}

Test(win_line, true_win) {
  Array* line = array_new(3).ok;

  for (int i = 0; i < line->capacity; i++) {
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
Test(win, win_straight_lines) {
  Matrix* board = board_new(3, 3);

  // char* str_board = matrix_to_string(board, (ToStringFn) square_to_string);
  
  int n_to_win = 3;
  for (int r = 0; r < board->rows; r++) {
    ///////////////
    // test rows
    ///////////////
    for (int c = 0; c < board->columns; c++) {
      Position pos = position_new(r, c);
      Square* sqr = (Square*) matrix_get(board, &pos).ok;
      sqr->mark = 'X';
    }

    // str_board = matrix_to_string(board, (ToStringFn) square_to_string);
    // printf("test r%d\n%s\n", r, str_board);

    bool result = win(board, n_to_win);
    cr_assert_eq(result, true);

    for (int c = 0; c < board->columns; c++) {
      Position pos = position_new(r, c);
      Square* sqr = (Square*) matrix_get(board, &pos).ok;
      sqr->mark = BLANK;
    }
    // printf("\n\n");

    ///////////////
    // test columns
    ///////////////
    for (int c = 0; c < board->columns; c++) {
      Position pos = position_new(c, r);
      Square* sqr = (Square*) matrix_get(board, &pos).ok;
      sqr->mark = 'X';
    }

    // str_board = matrix_to_string(board, (ToStringFn) square_to_string);
    // printf("test c%d\n%s\n", r, str_board);

    result = win(board, n_to_win);
    cr_assert_eq(result, true);

    for (int c = 0; c < board->columns; c++) {
      Position pos = position_new(c, r);
      Square* sqr = (Square*) matrix_get(board, &pos).ok;
      sqr->mark = BLANK;
    }
    // printf("\n\n");
  }

  board_free(&board);
}


Test(win, win_diagonal_lines) {
  Matrix* board = board_new(3, 3);

  // test left diagonal
  for (int c = 0; c < board->columns; c++) {
    Position pos = position_new(c, c);
    Square* sqr = (Square*) matrix_get(board, &pos).ok;
    sqr->mark = 'X';
  }
  // printf("%s\n", matrix_to_string(board, (ToStringFn) square_to_string));

  int n_to_win = 3;
  bool result = win(board, n_to_win);

  cr_assert_eq(result, true);

  // reset values
  for (int c = 0; c < board->columns; c++) {
    Position pos = position_new(c, c);
    Square* sqr = (Square*) matrix_get(board, &pos).ok;
    sqr->mark = BLANK;
  }


  // test right diagonal
  int col = board->columns - 1;
  for (int c = 0; c < board->columns; c++) {
    Position pos = position_new(c, col--);
    Square* sqr = (Square*) matrix_get(board, &pos).ok;
    sqr->mark = 'X';
  }
  // printf("%s\n", matrix_to_string(board, (ToStringFn) square_to_string));

  result = win(board, n_to_win);

  cr_assert_eq(result, true);

  board_free(&board);
}
