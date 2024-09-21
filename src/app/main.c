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
  printf("I use Arch, btw... :0");

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
    // repeat
    system("clear");
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
    bool p2s_turn =  false;

    if (round_count % 2 == 0) {
      p2s_turn = move_count % 2 != 0; 
    } else {
      p2s_turn = move_count % 2 == 0; 
    }

    if (p2s_turn) {
      sym = p2->symbol;
    }

    int mark_res = board_mark(board, &pos, sym);
    if (mark_res == 1) {
      continue;
    }
    ++move_count;

    if (move_count >= n_to_win) {
      winner = win(board, n_to_win);
    }

    if (winner) {
      // repeat
      system("clear");
      printf("%s  vs  %s\n\n", str_p1, str_p2);
      board_print(board);

      char* victor = p2s_turn ? p2->name : p1->name;
      printf("%s won!\n", victor);
      ++round_count;
      break;
    }

    if (move_count == board->capacity) {
      // repeat
      system("clear");
      printf("%s  vs  %s\n\n", str_p1, str_p2);
      board_print(board);

      printf("Draw!\n");
      break;
    }

  }

  player_free(&p1);
  player_free(&p2);
  ptr_free((void**) &str_p1);
  ptr_free((void**) &str_p2);
  matrix_free(&board, (FreeFn) square_free);

  return 0;
}
