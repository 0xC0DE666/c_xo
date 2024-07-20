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
