// ####################
// BOARD
// ####################

// POSITION

typedef struct {
  int row;
  int column;
} Position;

Position* position_new(int row, int column);
char* position_to_string(Position* position);


// SQUARE

typedef struct {
   Position* position;
  char mark;
} Square;

Square* square_new(Position* position, char mark);
char* square_to_string(Square* square);


// BOARD

typedef struct {
  int marks;
  char values[3][3];
} Board;

Board* board_new();
char* board_to_string(Board* board);
