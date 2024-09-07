#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "../libs/c_structs.h"

#include "utils/io.h"
#include "utils/misc.h"
#include "models/player.h"
#include "models/board.h"

int main() {
  printf("C XO\n");

  Player* p1 = player_new("Player 1", 'X');
  Player* p2 = player_new("Player 2", 'O');
  char* str_p1 = player_to_string(p1);
  char* str_p2 = player_to_string(p2);
 
  Matrix* board = board_new(3, 3);
  
  bool win = false;
  bool board_has_capacity = true;

  Position pos = position_new(1, 1);
  board_mark(board, &pos, 'X');

  while (board_has_capacity && win == false) {
    Matrix* blanks = matrix_map(board, (MatrixMapFn) square_is_blank);
    char* str_blanks = matrix_to_string(blanks, (ToStringFn) bool_to_str);

    printf("%s  vs  %s\n\n", str_p1, str_p2);
    board_print(board);
    printf("\nChoose a square to mark:\n");
    printf("%s\n", str_blanks);

    win = true;

    free(str_blanks);
    matrix_free(&blanks, (FreeFn) ptr_free);
  }


  player_free(&p1);
  player_free(&p2);
  free(str_p1);
  free(str_p2);

  matrix_free(&board, (FreeFn) square_free);
  return 0;
}
