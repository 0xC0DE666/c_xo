#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "../libs/c_structs.h"

#include "utils/io.h"
#include "models/player.h"
#include "models/board.h"

int main() {
  printf("C XO\n");

  Player* p1 = player_new("Player 1", 'X');
  Player* p2 = player_new("Player 2", 'O');
  Matrix* board = board_new(3, 3);

  bool win = false;
  bool board_has_capacity = true;

  Position pos = position_new(1, 1);
  Square* sqr = matrix_get(board, &pos);
  sqr->mark = 'X';

  while (board_has_capacity && win == false) {
    char* str_p1 = player_to_string(p1);
    char* str_p2 = player_to_string(p2);

    printf("%s  vs  %s\n\n", str_p1, str_p2);
    board_print(board);
    printf("\nChoose a square to mark:\n");

    free(str_p1);
    free(str_p2);

    win = true;
  }


  return 0;
}
