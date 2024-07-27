// ####################
// BOARD
// ####################

static const char BLANK = ' ';

// POSITION

typedef struct {
  int row;
  int column;
} Position;

Position* position_new(int row, int column);
void position_free(Position** position);
char* position_to_string(Position* position);


// SQUARE

typedef struct {
  Position* position;
  char mark;
} Square;

Square* square_new(Position* position, char mark);
void square_free(Square** square);
char* square_to_string(Square* square);


// BOARD

typedef struct {
  int marks;
  Square* squares[3][3];
} Board;

Board* board_new();
void board_free(Board** board);
char* board_to_string(Board* board);
void board_mark(Board* board, Position* position, char mark);
