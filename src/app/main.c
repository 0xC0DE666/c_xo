#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "../libs/c_structs.h"
#include "../libs/raylib.h"

#include "utils/utils.h"
#include "models/models.h"

void scoreboard_print(Player* p1, Player* p2) {
  player_print(p1);
  printf("  vs  ");
  player_print(p2);
  printf("\n\n");
}

int main() {
  printf("C XO\n");

  Player* p1 = player_new("Player 1", 'X');
  Player* p2 = player_new("Player 2", 'O');
  Grid* board = board_new(3, 3);
  
  int round_count = 1;
  int move_count = 0;
  int n_to_win = 3;

  bool end_game = false;

  while (!end_game) {
    // repeat
    system("clear");
    scoreboard_print(p1, p2);
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

    if (round_count % 2 != 0) {
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

    bool winner = false;
    bool draw = move_count == board->capacity;
    if (move_count >= n_to_win) {
      winner = win(board, n_to_win);
    }

    end_game = winner || draw;
    if (!end_game) {
      continue;
    }

    Player* player = p2s_turn ? p2 : p1;
    if (winner) {
      player->score++;
    }

    system("clear");
    scoreboard_print(p1, p2);
    board_print(board);

    if (winner) {
      printf("%s won!\n", player->name);
      sleep(2);
    }

    if (draw) {
      printf("Draw!\n");
      sleep(2);
    }

    bool play_again = ask_play_again();
    if (play_again) {
      ++round_count;
      move_count = 0;
      board_clear(board);
      end_game = false;
    }

    if (!play_again) {
      system("clear");
      scoreboard_print(p1, p2);
      board_print(board);
      printf("Game over.\n");
    }
  }

  player_free(&p1);
  player_free(&p2);
  grid_free(&board, (FreeFn) square_free);

  return 0;
}
