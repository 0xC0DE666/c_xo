#include <stdbool.h>
#include <string.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "board.h"

// ####################
// board
// ####################
Test(board, pass) {
  int result = 10;
  cr_assert_eq(result, 10);
}


// ####################
// board_new
// ####################
Test(board_new, _1) {
  Board *board = board_new();

  cr_assert_eq(board != NULL, true);
  cr_assert_eq(board->marks, 0);

  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      cr_assert_eq(board->values[r][c], ' ');
    }
  }
}

// ####################
// board_to_string
// ####################
// Test(board_to_string, _1) {
//   Board *board = board_new("Board 1", 'X');
// 
//   char *result= board_to_string(board);
//   char *expected = "Board 1 (X) 0";
// 
//   cr_assert_eq(strcmp(result, expected), 0);
// }
// 
// Test(board_to_string, _2) {
//   Board *board = board_new("Who?", 'G');
//   board->score = 666;
// 
//   char *result= board_to_string(board);
//   char *expected = "Who? (G) 666";
// 
//   cr_assert_eq(strcmp(result, expected), 0);
// }
