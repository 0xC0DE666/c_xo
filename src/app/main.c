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

  while (board_has_capacity && win == false) {
    char* str_p1 = player_to_string(p1);
    char* str_p2 = player_to_string(p2);
    char* str_board = matrix_to_string(board, (ToStringFn) square_to_string);

    printf("%s  vs  %s\n%s", str_p1, str_p2, str_board);
    printf("Choose a square to mark:\n");

    free(str_p1);
    free(str_p2);
    free(str_board);

    win = true;
  }


  return 0;
}
