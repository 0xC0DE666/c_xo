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
  
  int round_count = 1;
  int move_count = 0;
  bool winner = false;
  int n_to_win = 3;

  while (move_count < board->capacity && winner == false) {
    ++move_count;
    printf("%s  vs  %s\n\n", str_p1, str_p2);
    board_print(board);
    printf("\nChoose a square to mark:\n");

    int idx = get_index_to_mark(1, board->capacity);
    Position pos = index_to_position(board, idx);

    if (square_is_blank(board, &pos) == false) {
      system("clear");
      continue;
    }

    char sym = p1->symbol;
    bool p2s_turn = round_count % 2 == 0 && move_count % 2 != 0;

    if (p2s_turn) {
      sym = p2->symbol;
    }

    board_mark(board, &pos, sym);

    if (board->size == n_to_win) {
      winner = win(board, n_to_win);
    }

    if (winner) {
      char* victor = p2s_turn ? p2->name : p1->name;
      printf("%s won!\n", victor);
      ++round_count;
      break;
    }

    if (move_count == board->capacity) {
      printf("Draw!\n");
      break;
    }

    system("clear");
  }

  player_free(&p1);
  player_free(&p2);
  ptr_free((void**) &str_p1);
  ptr_free((void**) &str_p2);
  matrix_free(&board, (FreeFn) square_free);

  return 0;
}
