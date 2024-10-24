#include <stdbool.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../app/utils/utils.h"

// ####################
// string_new
// ####################
Test(string_new, _1) {
  char* str = string_new(32);

  cr_assert_eq(str == NULL, false);

  sprintf(str, "Some string...");

  char* expected = "Some string...";

  cr_assert_eq(strcmp(str, expected), false);

  string_free(&str);
}

// ####################
// string_free
// ####################
Test(string_free, _1) {
  char* string = string_new(5);

  cr_assert_eq(string == NULL, false);

  string_free(&string);

  cr_assert_eq(string, NULL);
}

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
