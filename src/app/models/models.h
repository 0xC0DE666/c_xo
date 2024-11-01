#include <stdbool.h>
#include <stdbool.h>

#include "../../libs/c_structs.h"

#ifndef MODELS_H
#define MODELS_H

// ####################
// PLAYER
// ####################
typedef struct {
  char* name;
  char symbol;
  int score;
} Player;

Player* player_new(char* name, char symbol);
void player_free(Player** player);
char* player_to_string(Player* player);
void player_print(Player* player);

void cpu_get_pos_to_mark(Grid* board);

// ####################
// BOARD
// ####################

// SQUARE
static const char UNMARKED = ' ';

typedef struct {
  Position position;
  char mark;
} Square;

Square* square_new(Position position, char mark);
void square_free(Square** const square);
char* square_to_string(Square* const square);
bool square_is_blank(Grid* const board, Position* const position);
void square_clear(Square* const square);
void square_mark(Square* const square, char mark);

// BOARD
Grid* board_new(int rows, int columns);
void board_free(Grid** const board);
void board_clear(Grid* const board);
void board_print(Grid* const board);
int board_mark(Grid* const board, Position* const position, char mark);

Position index_to_position(Grid* const board, int index);

// WIN
bool win_line(Array* line, int n_to_win);
bool win(Grid* board, int n_to_win);

#endif
