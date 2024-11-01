#include <stdlib.h>
#include <stdio.h>

#include "../utils/utils.h"
#include "models.h"

Player* player_new(char* name, char symbol) {
  Player* player = malloc(sizeof(Player));

  if (player == NULL) {
    return NULL;
  }

  player->name = name;
  player->symbol = symbol;
  player->score = 0;

  return player;
}

void player_free(Player** player) {
  free(*player);
  *player = NULL;
}

char* player_to_string(Player* player) {
  char* str = string_new(64);

  sprintf(
    str,
    "%s (%c) %d",
    player->name,
    player->symbol,
    player->score
  ); 

  return str;
}

void player_print(Player* player) {
  printf(
    "%s (%c) %d",
    player->name,
    player->symbol,
    player->score
  ); 
}

void cpu_get_pos_to_mark(Grid* board) {}
