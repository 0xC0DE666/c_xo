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
