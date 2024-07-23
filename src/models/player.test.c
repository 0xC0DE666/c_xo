#include <stdbool.h>
#include <string.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "player.h"

// ####################
// player_new
// ####################
Test(player_new, _1) {
  Player* player = player_new("Player 1", 'X');

  cr_assert_eq(player != NULL, true);
  cr_assert_eq(strcmp(player->name, "Player 1"), 0);
  cr_assert_eq(player->symbol, 'X');
  cr_assert_eq(player->score, 0);

  player_free(&player);
}

// ####################
// player_free
// ####################
Test(player_free, _1) {
  Player* player = player_new("Player 2", 'O');

  cr_assert_eq(player == NULL, false);

  player_free(&player);

  cr_assert_eq(player, NULL);
}

// ####################
// player_to_string
// ####################
Test(player_to_string, _1) {
  Player* player = player_new("Player 1", 'X');

  char* result= player_to_string(player);
  char* expected = "Player 1 (X) 0";

  cr_assert_eq(strcmp(result, expected), 0);
}
