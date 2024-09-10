#include <stdbool.h>
#include <stdbool.h>

#include "../../libs/c_structs.h"

// ####################
// BOARD
// ####################

// SQUARE
static const char BLANK = ' ';

typedef struct {
  Position position;
  char mark;
} Square;

Square* square_new(Position position, char mark);
void square_free(Square** square);
char* square_to_string(Square* square);
bool square_is_blank(Matrix* board, Position* position);

// BOARD
Matrix* board_new(int rows, int columns);
void board_free(Matrix** board);
void board_print(Matrix* board);
int board_mark(Matrix* board, Position* position, char mark);

Position index_to_position(Matrix* board, int index);

// WIN
bool win_line(Array* line, int n_to_win);
bool win(Matrix* board, int n_to_win);
