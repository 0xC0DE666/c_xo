typedef struct {
  int marks;
  char values[3][3];
} Board;

Board *board_new();
char *board_to_string(Board *board);
