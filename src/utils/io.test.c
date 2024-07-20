#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "io.h"

// ####################
// string_length
// ####################
Test(string_length, pass) {
  int result = string_length("");
  cr_assert_eq(result, 0);

  result = string_length("a");
  cr_assert_eq(result, 1);

  result = string_length("abc");
  cr_assert_eq(result, 3);
}
