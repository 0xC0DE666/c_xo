#include <stdbool.h>
#include <string.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "player.h"

// ####################
// player
// ####################
Test(player, pass) {
  int result = 10;
  cr_assert_eq(result, 10);
}


// ####################
// player_new
// ####################
Test(player_new, _1) {
  Player *player = player_new("Player 1", 'X');

  cr_assert_eq(player != NULL, true);
  cr_assert_eq(strcmp(player->name, "Player 1"), 0);
  cr_assert_eq(player->symbol, 'X');
  cr_assert_eq(player->score, 0);
}
