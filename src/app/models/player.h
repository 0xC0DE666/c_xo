typedef struct {
  char* name;
  char symbol;
  int score;
} Player;

Player* player_new(char* name, char symbol);
void player_free(Player** player);
char* player_to_string(Player* player);
