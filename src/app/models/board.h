#include <stdbool.h>
#include <stdbool.h>

#include "../../libs/c_structs.h"

// ####################
// BOARD
// ####################

static const char BLANK = ' ';

// SQUARE

typedef struct {
  Position position;
  char mark;
} Square;

Square* square_new(Position position, char mark);
void square_free(Square** square);
char* square_to_string(Square* square);

bool win_line(Array* line, unsigned n_to_win);
bool win(Matrix* board, unsigned n_to_win);
