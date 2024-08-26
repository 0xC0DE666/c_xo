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

// BOARD
Matrix* board_new(unsigned rows, unsigned columns);
void board_free(Matrix** board);

// WIN
bool win_line(Array* line, unsigned n_to_win);
bool win(Matrix* board, unsigned n_to_win);
