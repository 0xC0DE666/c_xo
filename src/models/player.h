typedef struct {
  char *name;
  char symbol;
  int score;
} Player;

Player *player_new(char *name, char symbol);
