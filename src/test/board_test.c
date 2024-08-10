#include <stdbool.h>
#include <string.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../app/utils/io.h"
#include "../app/models/board.h"

// ####################
// position_new
// ####################
Test(position_new, _1) {
  Position* position = position_new(1, 2);

  cr_assert_eq(position != NULL, true);
  cr_assert_eq(position->row, 1);
  cr_assert_eq(position->column, 2);

  position_free(&position);
}

// ####################
// position_free
// ####################
Test(position_free, _1) {
  Position* position = position_new(1, 2);

  cr_assert_eq(position == NULL, false);

  position_free(&position);

  cr_assert_eq(position, NULL);
}

// ####################
// position_to_string
// ####################
Test(position_to_string, _1) {
  Position* position = position_new(5, 3);

  char* result= position_to_string(position);
  char* expected = "(5, 3)";

  cr_assert_eq(strcmp(result, expected), 0);

  position_free(&position);
  string_free(&result);
}


// ####################
// square_new
// ####################
Test(square_new, _1) {
  Square* square = square_new(position_new(0, 1), 'O');

  cr_assert_eq(square != NULL, true);
  cr_assert_eq(square->position->row, 0);
  cr_assert_eq(square->position->column, 1);
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
// board_new
// ####################
Test(board_new, _1) {
  Board* board = board_new();

  cr_assert_eq(board != NULL, true);
  cr_assert_eq(board->marks, 0);

  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      cr_assert_eq(board->squares[r][c]->mark, BLANK);
    }
  }

  board_free(&board);
}

// ####################
// board_free
// ####################
Test(board_free, _1) {
  Board* board = board_new();

  cr_assert_eq(board == NULL, false);

  board_free(&board);

  cr_assert_eq(board, NULL);
}

// ####################
// board_to_string
// ####################
// Test(board_to_string, _1) {
//   Board* board = board_new("Board 1", 'X');
// 
//   char* result= board_to_string(board);
//   char* expected = "Board 1 (X) 0";
// 
//   cr_assert_eq(strcmp(result, expected), 0);
// }
// 
// Test(board_to_string, _2) {
//   Board* board = board_new("Who?", 'G');
//   board->score = 666;
// 
//   char* result= board_to_string(board);
//   char* expected = "Who? (G) 666";
// 
//   cr_assert_eq(strcmp(result, expected), 0);
// }

// ####################
// board_mark
// ####################
Test(board_mark, _1) {
  Board* board = board_new();
  Position* position = position_new(1, 1);

  board_mark(board, position, 'X');

  int row = position->row;
  int col = position->column;
  char result = board->squares[row][col]->mark;

  cr_assert_eq(result, 'X');

  board_free(&board);
  position_free(&position);
}

// ####################
// board_get_mark
// ####################
Test(board_get_mark, _1) {
  Board* board = board_new();
  Position* position = position_new(1, 1);

  board_mark(board, position, 'X');

  int row = position->row;
  int col = position->column;
  char result = board_get_mark(board, position);

  cr_assert_eq(result, 'X');

  board_free(&board);
  position_free(&position);
}

// ####################
// check_line
// ####################
Test(check_line, _1) {
  char line1[] = {' ', 'X', ' '};
  bool result = check_line(line1, 3);

  cr_assert_eq(result, false);
  
  char line2[] = {'X', 'X', 'X'};
  result = check_line(line2, 3);

  cr_assert_eq(result, true);
}
