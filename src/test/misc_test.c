#include <stdlib.h>
#include <stdbool.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../app/utils/misc.h"

// ####################
// ptr_free
// ####################
Test(ptr_free, _1) {
  int* i = malloc(sizeof(int));
  *i = 10;

  cr_assert_eq(*i, 10);

  ptr_free((void**) &i);

  cr_assert_eq(i == NULL, true);
}

// ####################
// bool_to_str
// ####################
Test(bool_to_str, _1) {
  bool t = true;
  bool f = false;

  char* str_t = bool_to_str(&t);
  char* str_f = bool_to_str(&f);

  cr_assert_eq(strcmp(str_t, "true"), 0);
  cr_assert_eq(strcmp(str_f, "false"), 0);

  ptr_free((void**) &str_t);
  ptr_free((void**) &str_f);
}
