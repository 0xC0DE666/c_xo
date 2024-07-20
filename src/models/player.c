#include <stdlib.h>
#include <stdio.h>

#include "player.h"

Player *player_new(char *name, char symbol) {
  Player *player = malloc(sizeof(Player));

  if (player == NULL) {
    return NULL;
  }

  player->name = name;
  player->symbol = symbol;
  player->score = 0;

  return player;
}

char *player_to_string(Player *player) {
  char *str = malloc(100 * sizeof(char));

  sprintf(
    str,
    "%s (%c) %d",
    player->name,
    player->symbol,
    player->score
  ); 

  return str;
}
