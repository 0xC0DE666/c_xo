#include <stdlib.h>

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
