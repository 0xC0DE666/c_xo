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
void square_free(Square** const square);
char* square_to_string(Square* const square);
bool square_is_blank(Matrix* const board, Position* const position);
void square_clear(Square* const square);
void square_mark(Square* const square, char mark);

// BOARD
Matrix* board_new(int rows, int columns);
void board_free(Matrix** const board);
void board_clear(Matrix* const board);
void board_print(Matrix* const board);
int board_mark(Matrix* const board, Position* const position, char mark);

Position index_to_position(Matrix* const board, int index);

// WIN
bool win_line(Array* line, int n_to_win);
bool win(Matrix* board, int n_to_win);
